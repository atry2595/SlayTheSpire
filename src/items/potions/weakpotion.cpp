#include "weakpotion.h"
#include "combat/attack_info.h"
#include "items/powers/powerfactory.h"

weakPotion::weakPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Weak Potion"), tr("Apply 3 Weak to target enemy."), owner_init)
{}

void weakPotion::play(playInfo& info){

    for (auto item : info.target_list) {
        abstractPower* np = PowerFactory::createPower(powerID::weak, item, amount);
        item->add_power(info.actions, np);
    }

}

QString weakPotion::get_story() {
    return (QObject::tr("The Weak Potion, a pink, tasteless liquid whose very light seems hesitant, as if it doubts its own existence.\nBut when splashed on the enemy's face, their strikes grow limp and lifeless, as if all will to fight has been dissolved in this featureless fluid."));
}
