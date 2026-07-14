#include "shame.h"
#include "items/powers/powerfactory.h"

shame::shame()
    :abstractCurseCard(tr("Shame"), "", 0, false, false, false, false)
{
    base_is_playable = playable = false;
    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s+= tr("At the end of your turn, gain 1 Frail.");
    base_description = description = s;
}

QString shame::generate_description(){

    QString s;
    if (!playable) s += tr("Unplayable.\n");
    s+= tr("At the end of your turn, gain 1 Frail.");
    return s;
}

void shame::play(playInfo& play_info){

    play_info.attacker->add_power(play_info.actions, PowerFactory::createPower(powerID::frail, play_info.attacker, 1));
}

void shame::upgrade(){
}

void shame::base_upgrade(){
}


void shame::hand_turn_end(playInfo& info){
    play(info);
}




