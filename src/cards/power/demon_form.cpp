#include "demon_form.h"
#include "categories/powers.h"
#include "items/powers/powerfactory.h"

demon_form::demon_form()
    :abstractPowerCard(tr("Demon Form"), "", 3)
{
    QString s;
    s += tr("At the start of your turn, gain %1 Strength.").arg(effect);
    base_description = description = s;
}

QString demon_form::generate_description(){

    QString s;
    s += tr("At the start of your turn, gain %1 Strength.").arg(effect);
    return s;
}

void demon_form::play(playInfo& play_info){
    abstractEntity* player = play_info.attacker;
    abstractPower* p = PowerFactory::createPower(powerID::demon_form, player, effect);
    player->add_power(p);
}

void demon_form::upgrade(){
    effect = 3;
    is_upgraded = true;
    description = generate_description();
}

void demon_form::base_upgrade(){
    base_effect = effect = 3;
    base_is_upgraded = true;
    base_description = generate_description();

    combat_reset();
}





