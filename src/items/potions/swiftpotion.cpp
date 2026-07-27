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

QString swiftPotion::get_story() {
    return (QObject::tr("The Swift Potion, silver and fluid as mercury, slides restlessly in its bottle.\nThree sips of this liquid metal, and suddenly the traveler's feet turn to wind—dancing and elusive."));
}
