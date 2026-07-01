#include "barricade.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

barricade::barricade()
    :abstractPowerCard(tr("Barricade"), "", 3)
{
    QString s;
    s += tr("Block is not removed at the start of your turn.");
    base_description = description = s;
}

QString barricade::generate_description(){

    QString s;
    s += tr("Block is not removed at the start of your turn.");
    return s;
}

void barricade::play(playInfo& play_info){
    abstractEntity* player = play_info.attacker;
    abstractPower* p = PowerFactory::createPower(powerID::barricade, player, 1);
    player->add_power(p);
}

void barricade::upgrade(){
    energy = 2;
    is_upgraded = true;
    description = generate_description();
}

void barricade::base_upgrade(){
    base_energy = energy = 2;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





