#include "game_action.h"
#include "play_info.h"
#include "entity/abstractentity.h"
#include "cards/abstractcard.h"
#include "items/potions/abstractpotion.h"
#include "entity/ironclad.h"
#include "assetsManager/soundmanager.h"

game_action::game_action(combatEvent* eve):event(eve) {}

attackResult game_action::attack(attackInfo& info) {

    if (info.attacker) {
        info.attacker->modify_attack(info);
        emit event->attack_started(info);
    }

    attackResult res(info);

    for (abstractEntity* target : info.target_list){
        damageInfo dmg;
        dmg.attacker = info.attacker;
        dmg.target = target;
        dmg.damage = info.damage;
        dmg.attack_type = info.attack_type;
        auto r = this->apply_damage(dmg);
        res.results.push_back(r);
    }

    emit event->afterAttack(res);
    return res;
}

damageResult game_action::apply_damage(damageInfo& info) {

    damageResult res;

    auto target = info.target;

    res.target = target;
    res.attacker = info.attacker;

    target->modify_incoming_damage(info);
    emit event->damage_before_blocking(info);

    int dmg = info.damage;

    int block = target->get_block();

    if (block && info.block_active){
        if (dmg < block){
            res.blocked = dmg;
            target->set_block(block - dmg);
            blockingInfo bl;
            bl.block = -dmg;
            bl.owner = target;
            emit event->block_changed(bl);

            emit event->entityUpdate(info.target);
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
            emit event->entityUpdate(info.target);
        }
    }


    int hp = target->get_hp();
    res.final_damage = dmg;
    if (dmg == 0) return res;

    emit event->damage_before_taken(info);

    if (hp > dmg){
        target->set_hp(hp - dmg);
        info.damage = dmg;
        info.target->damage_applied(*this);
        emit event->damage_applied(info);
        emit event->hp_changed(info.target, hp, hp - dmg);
        emit event->entityUpdate(info.target);
    }
    else{
        target->set_hp(0);
        res.killed = true;
        emit event->hp_changed(info.target, hp, 0);
        emit event->entityUpdate(info.target);
        emit event->entity_killed(target);
        if (target->get_ID() == entityID::ironclad){
            auto plyr = dynamic_cast<ironclad*>(target);
            for (auto item : plyr->get_potion_list()){
                if (item->get_ID() == potionID::fairy_in_a_bottle){
                    drinkPotionInfo pot_inf;
                    pot_inf.potion = item;
                    pot_inf.owner = plyr;
                    pot_inf.target_list = {};

                    plyr->drink_potion(pot_inf);
                }
            }
        }
        if (target->get_hp() <= 0){
            emit event->entity_removed(target);
        }
    }

    return res;
}

void game_action::apply_block(blockingInfo& info){

    auto sound = soundManager::instance();

    if (info.affected_by_other){
        info.owner->modify_blocking(info);
        emit event->before_block_set(info);
    }

    if (info.owner->get_block() == 0) sound.playSoundEffect(SoundEffect::setShield);
    int new_block = info.owner->get_block() + info.block;
    info.owner->set_block(new_block);
    info.block = new_block;

    emit event->block_changed(info);
    emit event->entityUpdate(info.owner);
}


void game_action::play_card(playCardInfo& info) {

    playInfo ply(*this);
    ply.attacker = info.owner;
    ply.target_list = info.target_list;

    info.card->play(ply);
    emit event->card_played(info);
}


void game_action::drink_potion(drinkPotionInfo& info){

    playInfo ply(*this);
    ply.attacker = info.owner;
    ply.target_list = info.target_list;

    info.potion->play(ply);
    emit event->potion_used(info.potion);
}


void game_action::heal(healInfo& info){
    int oldHP = info.owner->get_hp();
    int newHP = std::min(oldHP + info.value, info.owner->get_max_hp());
    info.owner->set_hp(newHP);
    emit event->hp_changed(info.owner, oldHP, newHP);
    emit event->entityUpdate(info.owner);
}
