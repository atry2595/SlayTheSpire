#include "dexteritypotion.h"
#include "combat/attack_info.h"
#include "items/powers/powerfactory.h"

dexterityPotion::dexterityPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Dexterity Potion"), tr("Gain 2 Dexterity."), owner_init)
{}

void dexterityPotion::play(playInfo& info){

    abstractPower* np = PowerFactory::createPower(powerID::dexterity, info.attacker, 2);
    info.attacker->add_power(info.actions, np);

}