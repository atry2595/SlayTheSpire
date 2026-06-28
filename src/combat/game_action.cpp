#include "game_action.h"

game_action::game_action(combatEvent* eve):event(eve) {}

void game_action::attack(attackInfo& info) {

    emit event->attack_started(info);

    for (Entity* target : info.target_list){
        damageInfo dmg;
        dmg.attacker = info.attacker;
        dmg.target = target;
        dmg.damage = info.damage;
        // this->damage(dmg);
    }
}
