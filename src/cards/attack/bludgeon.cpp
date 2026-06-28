#include "bludgeon.h"

bludgeon::bludgeon(bool upgraded_init)
    :abstractAttackCard(tr("bludgeon"), "", 3, 32, upgraded_init, false, false, false, false)
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
    base_damage = 42;
    is_upgraded = true;
    base_description = generate_description();

    reset();
}




