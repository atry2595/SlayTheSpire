#include "berserk.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

berserk::berserk()
    :abstractPowerCard(tr("Berserk"), "", 0, false, false, false, false)
{
    QString s;
    s += tr("Gain %1 Vulnerable.\n").arg(effect);
    s += tr("At the start of your turn, gain 1 Energy");
    base_description = description = s;
}

QString berserk::generate_description(){

    QString s;
    s += tr("Gain %1 Vulnerable.\n").arg(effect);
    s += tr("At the start of your turn, gain Energy");
    return s;
}

void berserk::play(playInfo& play_info){
    abstractEntity* player = play_info.attacker;

    abstractPower* p1 = PowerFactory::createPower(powerID::vulnerable, player, effect);
    player->add_power(play_info.actions, p1);

    abstractPower* p2 = PowerFactory::createPower(powerID::berserk, player, 1);
    player->add_power(play_info.actions, p2);
}

void berserk::upgrade(){
    effect = 1;
    is_upgraded = true;
    description = generate_description();
}

void berserk::base_upgrade(){
    base_effect = effect = 1;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





