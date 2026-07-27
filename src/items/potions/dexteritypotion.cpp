#include "dexteritypotion.h"
#include "combat/attack_info.h"
#include "items/powers/powerfactory.h"

dexterityPotion::dexterityPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Dexterity Potion"), tr("Gain 2 Dexterity."), owner_init)
{}

void dexterityPotion::play(playInfo& info){

    abstractPower* np = PowerFactory::createPower(powerID::dexterity, info.attacker, amount);
    info.attacker->add_power(info.actions, np);

}

QString dexterityPotion::get_story() {
    return (QObject::tr("The Dexterity Potion, a green liquid with a soft glimmer—two drops of pure slipperiness.\nThe traveler drinks, and for the entire battle, every blow slides off cheaper than before, as if the very concept of \"being hit\" has been diluted for them."));
}
