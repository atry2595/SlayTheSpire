#include "doubt.h"
#include "items/powers/powerfactory.h"

doubt::doubt()
    :abstractCurseCard(tr("Doubt"), "", 0, false, false, false, false)
{
    base_is_playable = playable = false;
    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s+= tr("At the end of your turn, gain 1 Weak.");
    base_description = description = s;
}

QString doubt::generate_description(){

    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s+= tr("At the end of your turn, gain 1 Weak.");
    return s;
}

void doubt::play(playInfo& play_info){

    play_info.attacker->add_power(play_info.actions, PowerFactory::createPower(powerID::weak, play_info.attacker, 1));
}

void doubt::upgrade(){
}

void doubt::base_upgrade(){
}


void doubt::hand_turn_end(playInfo& info){
    play(info);
}




