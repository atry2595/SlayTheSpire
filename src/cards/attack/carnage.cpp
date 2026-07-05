#include "carnage.h"

carnage::carnage()
    :abstractAttackCard(tr("carnage"), "", 1, 20, false, false, true, false)
{
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    if (is_ethereal) s += tr("\nEthereal");

    base_description = description = s;
}

QString carnage::generate_description(){
    QString s;
    s += tr("Deal %1 damage.").arg(damage);
    if (is_ethereal) s += tr("\nEthereal");

    return s;
}

void carnage::play(playInfo& play_info){
    perform_attack(play_info.attacker, play_info.target_list, play_info.actions);
}

void carnage::upgrade(){
    damage = 28;
    is_upgraded = true;
    description = generate_description();
}

void carnage::base_upgrade(){
    base_damage = damage =28;
    is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}