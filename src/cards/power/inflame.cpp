#include "inflame.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

inflame::inflame()
    :abstractPowerCard(tr("Inflame"), "", 1)
{
    QString s;
    s += tr("Gain %1 Strength.").arg(effect);
    base_description = description = s;
}

QString inflame::generate_description(){

    QString s;
    s += tr("Gain %1 Strength.").arg(effect);
    return s;
}

void inflame::play(playInfo& play_info){
    abstractEntity* player = play_info.attacker;
    abstractPower* p = PowerFactory::createPower(powerID::strength, player, effect);
    player->add_power(p);
}

void inflame::upgrade(){
    effect = 3;
    is_upgraded = true;
    description = generate_description();
}

void inflame::base_upgrade(){
    base_effect = effect = 3;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





