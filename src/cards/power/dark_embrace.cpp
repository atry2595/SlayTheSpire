#include "dark_embrace.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

dark_embrace::dark_embrace()
    :abstractPowerCard(tr("Dark Embrace"), "", 2, false, false, false, false)
{
    QString s;
    s += tr("Whenever a card is Exhausted, draw 1 card.");
    base_description = description = s;
}

QString dark_embrace::generate_description(){

    QString s;
    s += tr("Whenever a card is Exhausted, draw 1 card.");
    return s;
}

void dark_embrace::play(playInfo& play_info){
    abstractEntity* player = play_info.attacker;
    abstractPower* p = PowerFactory::createPower(powerID::dark_embrace, player, 1);
    player->add_power(play_info.actions, p);
}

void dark_embrace::upgrade(){
    energy = 1;
    is_upgraded = true;
    description = generate_description();
}

void dark_embrace::base_upgrade(){
    base_energy = energy = 1;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





