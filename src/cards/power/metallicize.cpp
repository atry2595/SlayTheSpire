#include "metallicize.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

metallicize::metallicize()
    :abstractPowerCard(tr("Metallicize"), "", 1)
{
    QString s;
    s += tr("At the end of your turn, gain %1 Block.").arg(effect);
    base_description = description = s;
}

QString metallicize::generate_description(){

    QString s;
    s += tr("At the end of your turn, gain %1 Block.").arg(effect);
    return s;
}

void metallicize::play(playInfo& play_info){
    abstractEntity* player = play_info.attacker;
    abstractPower* p = PowerFactory::createPower(powerID::metallicize, player, effect);
    player->add_power(play_info.actions, p);
}

void metallicize::upgrade(){
    effect = 4;
    is_upgraded = true;
    description = generate_description();
}

void metallicize::base_upgrade(){
    base_effect = effect = 4;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





