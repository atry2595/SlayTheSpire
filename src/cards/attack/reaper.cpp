#include "reaper.h"

reaper::reaper()
    :abstractAttackCard(tr("Reaper"), "", 2, 4, true, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage to ALL enemies. Heal HP equal to unblocked damage.").arg(damage);
    if (is_exhaust) s += tr("\nExhaust");
    base_description = description = s;
}

QString reaper::generate_description(){

    QString s;
    s += tr("Deal %1 damage to ALL enemies. Heal HP equal to unblocked damage.").arg(damage);
    if (is_exhaust) s += tr("\nExhaust");
    return s;
}

void reaper::play(playInfo& play_info){

    attackResult res = perform_attack(play_info.attacker, play_info.target_list, play_info.actions);

    for (auto item : res.results){
        play_info.attacker->set_hp(play_info.attacker->get_hp() + item.final_damage);
    }

}

void reaper::upgrade(){
    damage = 5;
    is_upgraded = true;
    description = generate_description();
}

void reaper::base_upgrade(){
    base_damage = damage = 5;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}

void reaper::combat_reset() {
    abstractAttackCard::combat_reset();
}




