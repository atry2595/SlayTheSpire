#include "feel_no_pain.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

feel_no_pain::feel_no_pain()
    :abstractPowerCard(tr("Feel No Pain"), "", 1, false, false, false, false)
{
    QString s;
    s += tr("Whenever a card is Exhausted, gain %1 Block.").arg(effect);
    base_description = description = s;
}

QString feel_no_pain::generate_description(){

    QString s;
    s += tr("Whenever a card is Exhausted, gain %1 Block.").arg(effect);
    return s;
}

void feel_no_pain::play(playInfo& play_info){
    abstractEntity* player = play_info.attacker;
    abstractPower* p = PowerFactory::createPower(powerID::feel_no_pain, player, effect);
    player->add_power(p);
}

void feel_no_pain::upgrade(){
    effect = 4;
    is_upgraded = true;
    description = generate_description();
}

void feel_no_pain::base_upgrade(){
    base_effect = effect = 4;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





