#include "twin_strike.h"

twin_strike::twin_strike(bool upgraded_init)
    :abstractAttackCard(tr("twin_strike"), "", 1, 5, upgraded_init, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage twice.").arg(damage);
    base_description = description = s;
}

QString twin_strike::generate_description(){
    return tr("Deal %1 damage twice.").arg(damage);
}

void twin_strike::play(playInfo& play_info){
    for (int i = 0; i<2; i++)
    perform_attack(play_info.attacker, play_info.target_list, play_info.actions);
}

void twin_strike::upgrade(){
    damage = 7;
    is_upgraded = true;
    description = generate_description();
}

void twin_strike::base_upgrade(){
    base_damage = 7;
    is_upgraded = true;
    base_description = generate_description();

    reset();
}




