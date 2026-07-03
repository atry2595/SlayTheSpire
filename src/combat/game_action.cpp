#include "game_action.h"
#include "play_info.h"
#include "entity/abstractentity.h"
#include "cards/abstractcard.h"
#include "items/potions/abstractpotion.h"

game_action::game_action(combatEvent* eve):event(eve) {}

attackResult game_action::attack(attackInfo& info) {

    if (info.attacker) {
        info.attacker->modify_attack(info);
        emit event->attack_started(info);
    }

    attackResult res;

    for (abstractEntity* target : info.target_list){
        damageInfo dmg;
        dmg.attacker = info.attacker;
        dmg.target = target;
        dmg.damage = info.damage;
        res.results.push_back(this->apply_damage(dmg));
    }

    return res;
}

damageResult game_action::apply_damage(damageInfo& info) {

    damageResult res;

    auto target = info.target;

    target->modify_incoming_damage(info);
    emit event->before_damage_taken(info);

    int dmg = info.damage;

    int block = target->get_block();

    if (block){
        if (dmg < block){
            res.blocked = dmg;
            target->set_block(block - dmg);
            blockingInfo bl;
            bl.block = -dmg;
            bl.owner = target;
            emit event->block_changed(bl);

            return res;
        }
        else {
            res.blocked = block;
            target->set_block(0);
            blockingInfo bl;
            bl.block = -block;
            bl.owner = target;
            emit event->block_break(bl);

            dmg -= block;
        }
    }

    int hp = target->get_hp();
    res.final_damage = dmg;

    if (hp > dmg){
        target->set_hp(hp - dmg);
        info.damage = dmg;
        info.target->damage_applied(*this);
        emit event->damage_applied(info);
    }
    else{
        target->set_hp(0);
        res.killed = true;
        emit event->entity_killed(target);
    }

    return res;
}

void game_action::apply_block(blockingInfo& info){

    if (info.affected_by_other){
        info.owner->modify_blocking(info);
        emit event->before_block_set(info);
    }

    int new_block = info.owner->get_block() + info.block;
    info.owner->set_block(new_block);
    info.block = new_block;

    emit event->block_changed(info);
}


void game_action::play_card(playCardInfo& info) {

    playInfo ply(*this);
    ply.attacker = info.owner;
    ply.target_list = info.target_list;

    info.card->play(ply);
}


void game_action::drink_potion(drinkPotionInfo& info){

    playInfo ply(*this);
    ply.attacker = info.owner;
    ply.target_list = info.target_list;

    info.potion->play(ply);
}







