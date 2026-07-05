#include "fearpotion.h"
#include "combat/attack_info.h"
#include "items/powers/powerfactory.h"

fearPotion::fearPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Fear Potion"), tr("Apply 3 Vulnerable to target enemy."), owner_init)
{}

void fearPotion::play(playInfo& info){

    for (auto item : info.target_list) {
        abstractPower* np = PowerFactory::createPower(powerID::vulnerable, item, amount);
        item->add_power(info.actions, np);
    }

}