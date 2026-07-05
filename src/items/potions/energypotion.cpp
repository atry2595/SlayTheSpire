#include "energypotion.h"
#include "combat/attack_info.h"
#include "entity/ironclad.h"

energyPotion::energyPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Energy Potion"), tr("Gain 2 Energy."), owner_init)
{}

void energyPotion::play(playInfo& info){

    ironclad* player = dynamic_cast<ironclad*>(info.attacker);
    player->set_energy(player->get_energy() + 2);

}