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

QString strengthPotion::get_story() {
    return (QObject::tr("The Strength Potion, dark red like old blood, with sediment of concentrated rage at the bottom.\nThe traveler drinks and suddenly their muscles contract with ancestral violence, as if generations of warriors have awakened in their veins."));
}
