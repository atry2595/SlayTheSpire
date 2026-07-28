#include "bludgeon.h"

bludgeon::bludgeon()
    :abstractAttackCard(tr("bludgeon"), "", 3, 32, false, false, false, false)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    base_description = description = s;
}

QString bludgeon::generate_description(){
    return tr("Deal %1 damage.").arg(damage);
}

void bludgeon::play(playInfo& play_info){
    perform_attack(play_info.attacker, play_info.target_list, play_info.actions);
}

void bludgeon::upgrade(){
    damage = 42;
    is_upgraded = true;
    description = generate_description();
}

void bludgeon::base_upgrade(){
    base_damage = damage =42;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}




