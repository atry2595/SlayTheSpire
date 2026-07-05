#include "brutality.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

brutality::brutality()
    :abstractPowerCard(tr("Brutality"), "", 0, false, false, false, false)
{
    QString s;
    if (is_initial) s += tr("Innate.\n");
    s += tr("At the start of your turn, lose 1 HP and draw 1 card.");
    base_description = description = s;
}

QString brutality::generate_description(){

    QString s;
    if (is_initial) s += tr("Innate.\n");
    s += tr("At the start of your turn, lose 1 HP and draw 1 card.");
    return s;
}

void brutality::play(playInfo& play_info){
    abstractEntity* player = play_info.attacker;
    abstractPower* p = PowerFactory::createPower(powerID::brutality, player, 1);
    player->add_power(play_info.actions, p);
}

void brutality::upgrade(){
    is_initial = true;
    is_upgraded = true;
    description = generate_description();
}

void brutality::base_upgrade(){
    base_is_initial = is_initial = true;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





