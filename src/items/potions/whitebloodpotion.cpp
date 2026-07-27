#include "whitebloodpotion.h"
#include "combat/attack_info.h"
#include "entity/abstractentity.h"

whiteBloodPotion::whiteBloodPotion(abstractEntity* owner_init)
    :abstractPotion(tr("White Blood Potion"), tr("Heal for 20% of your Max HP."), owner_init)
{}

void whiteBloodPotion::play(playInfo& info){

    healInfo h_info;
    h_info.owner = info.attacker;
    h_info.value = (int)info.attacker->get_max_hp() * amount;

    info.actions.heal(h_info);

}

QString whiteBloodPotion::get_story() {
    return (QObject::tr("The White Blood Potion, milky with silver veins, swirls silently in its bottle like a miniature galaxy.\nThe traveler drinks and their blood briefly turns to liquid metal, wounds mending not with flesh but with steel."));
}
