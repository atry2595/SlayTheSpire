#include "energypotion.h"
#include "combat/attack_info.h"
#include "entity/ironclad.h"

energyPotion::energyPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Energy Potion"), tr("Gain 2 Energy."), owner_init)
{}

void energyPotion::play(playInfo& info){

    ironclad* player = dynamic_cast<ironclad*>(info.attacker);
    player->set_energy(player->get_energy() + amount);

}

QString energyPotion::get_story() {
    return (QObject::tr("The Energy Potion, a golden liquid glowing in the dark, a pulse made of lightning.\nThe traveler drinks it and their veins awaken with a fresh current of possibility, as if time pauses just to let them catch their breath."));
}
