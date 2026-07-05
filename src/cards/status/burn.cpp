#include "burn.h"

burn::burn()
    :abstractStatusCard(tr("Burn"), "", 0, false, false, false, false)
{
    base_is_playable = playable = false;
    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s += tr("At the end of your turn, take %1 damage.\n").arg(dmg);
    base_description = description = s;
}

QString burn::generate_description(){

    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s += tr("At the end of your turn, take %1 damage.\n").arg(dmg);
    return s;
}

void burn::play(playInfo& play_info){
    damageInfo info;
    info.damage = dmg;
    info.attacker = nullptr;
    info.target = play_info.attacker;
    play_info.actions.apply_damage(info);
}

void burn::upgrade(){


}

void burn::base_upgrade(){
}

void burn::curse_upgrade(){
    base_dmg = dmg = 4;
    is_upgraded = true;
    base_description = generate_description();
}


void burn::hand_turn_end(playInfo& play_info){
    play(play_info);
}


