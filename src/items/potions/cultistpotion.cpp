#include "cultistpotion.h"
#include "combat/attack_info.h"
#include "items/powers/powerfactory.h"

cultistPotion::cultistPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Cultist Potion"), tr("Gain 1 Ritual."), owner_init)
{}

void cultistPotion::play(playInfo& info){

    abstractPower* np = PowerFactory::createPower(powerID::ritual, info.attacker, amount);
    info.attacker->add_power(info.actions, np);

}