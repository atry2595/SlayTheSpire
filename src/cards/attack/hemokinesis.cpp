#include "hemokinesis.h"

hemokinesis::hemokinesis()
    :abstractAttackCard(tr("Hemokinesis"), "", 1, 15, false, false, false, false)
{
    QString s;
    s += tr("Lose %1 HP.").arg(dmg);
    s += tr("\nDeal %1 damage.").arg(damage);
    base_description = description = s;
}

QString hemokinesis::generate_description(){
    QString s;
    s += tr("Lose %1 HP.").arg(dmg);
    s += tr("\nDeal %1 damage.").arg(damage);
    return s;
}

void hemokinesis::play(playInfo& play_info){
    perform_attack(play_info.attacker, play_info.target_list, play_info.actions);

    damageInfo info;
    info.damage = dmg;
    info.attacker = nullptr;
    info.target = play_info.attacker;

    play_info.actions.apply_damage(info);
}

void hemokinesis::upgrade(){
    damage = 20;
    is_upgraded = true;
    description = generate_description();
}

void hemokinesis::base_upgrade(){
    base_damage = damage = 20;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}




