#include "whirlwind.h"
#include "entity/ironclad.h"

whirlwind::whirlwind()
    :abstractAttackCard(tr("Whirlwind"), "", 0, 5, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage to ALL enemies X times.").arg(damage);
    base_description = description = s;
}

QString whirlwind::generate_description(){

    QString s;
    s += tr("Deal %1 damage to ALL enemies X times.").arg(damage);
    return s;
}

void whirlwind::play(playInfo& play_info){

    ironclad* player = dynamic_cast<ironclad*>(play_info.attacker);

    if (player) {
        int repeat = player->get_energy();

        for (int i = 0; i<repeat; i++) {
            perform_attack(play_info.attacker, play_info.target_list, play_info.actions);
        }

        player->consume_all_energy();
    }
}

void whirlwind::upgrade(){
    damage = 8;
    is_upgraded = true;
    description = generate_description();
}

void whirlwind::base_upgrade(){
    base_damage = damage = 8;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void whirlwind::combat_reset() {
    abstractAttackCard::combat_reset();
}




