#include "game_action.h"

game_action::game_action(combatEvent* eve):event(eve) {}

void game_action::attack(attackInfo& info) {

    info.attacker->modify_attack(info);
    emit event->attack_started(info);

    for (abstractEntity* target : info.target_list){
        damageInfo dmg;
        dmg.attacker = info.attacker;
        dmg.target = target;
        dmg.damage = info.damage;
        this->apply_damage(dmg);
    }
}

void game_action::apply_damage(damageInfo& info) {

    auto target = info.target;

    target->modify_incoming_damage(info);
    emit event->before_damage_taken(info);

    int dmg = info.damage;

    int block = target->get_block();

    if (block){
        if (dmg < block){
            target->set_block(block - dmg);
            emit event->block_changed(target, block - dmg);
        }
        else {
            target->set_block(0);
            emit event->block_break(target);

            dmg -= block;
        }
    }

    int hp = target->get_hp();

    if (hp > dmg){
        target->set_hp(hp - dmg);
        info.damage = dmg;
        emit event->damage_applied(info);
    }
    else{
        target->set_hp(0);
        emit event->entity_killed(target);
    }
}

void game_action::apply_block(blockingInfo& info){

    if (info.affected_by_other){
        info.owner->modify_blocking(info);
        emit event->before_block_set(info);
    }

    int new_block = info.owner->get_block() + info.block;
    info.owner->set_block(new_block);

    emit event->block_changed(info.owner, info.owner->get_block());
}