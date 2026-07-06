#include "strengthpotion.h"
#include "combat/attack_info.h"
#include "items/powers/powerfactory.h"

strengthPotion::strengthPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Strength Potion"), tr("Gain 2 strength."), owner_init)
{}

void strengthPotion::play(playInfo& info){

    abstractPower* np = PowerFactory::createPower(powerID::strength, info.attacker, amount);
    info.attacker->add_power(info.actions, np);

}