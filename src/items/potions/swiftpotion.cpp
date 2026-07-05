#include "swiftpotion.h"
#include "combat/attack_info.h"
#include "entity/ironclad.h"

swiftPotion::swiftPotion(abstractEntity* owner_init)
    :abstractPotion(tr("Swift Potion"), tr("Draw 3 card."), owner_init)
{}

void swiftPotion::play(playInfo& info){

    ironclad* player = dynamic_cast<ironclad*>(info.attacker);
    for (int i = 0; i < amount; i++) player->draw_card();

}