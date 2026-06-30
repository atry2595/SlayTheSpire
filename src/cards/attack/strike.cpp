#include "strike.h"

strike::strike()
    :abstractAttackCard(tr("strike"), "", 1, 6, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    base_description = description = s;
}

QString strike::generate_description(){
    return tr("Deal %1 damage.").arg(damage);
}

void strike::play(playInfo& play_info){
    perform_attack(play_info.attacker, play_info.target_list, play_info.actions);
}

void strike::upgrade(){
    damage = 9;
    is_upgraded = true;
    description = generate_description();
}

void strike::base_upgrade(){
    base_damage = 9;
    base_is_upgraded = true;
    base_description = generate_description();

    reset();
}




