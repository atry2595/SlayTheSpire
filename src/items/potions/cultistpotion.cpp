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

QString cultistPotion::get_story() {
    return (QObject::tr("The Cultist Potion, a blue liquid that whispers \"Caw!\" with every shake.\nThe traveler drinks and suddenly the duck-like voice of power awakens in their throat, as if they've momentarily become a worshipper of the Spire, ripe for ascension."));
}
