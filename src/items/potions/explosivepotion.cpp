#include "explosivepotion.h"
#include "combat/attack_info.h"
#include "entity/ironclad.h"

explosivePotion::explosivePotion(abstractEntity* owner_init)
    :abstractPotion(tr("Explosive Potion"), tr("Deal 10 damage to all enemies."), owner_init)
{}

void explosivePotion::play(playInfo& info){

    attackInfo attack_inf;
    attack_inf.attacker = nullptr;
    attack_inf.damage = amount;
    attack_inf.target_list = info.target_list;
    attack_inf.attack_type = attackType::potion;
    info.actions.attack(attack_inf);

}

QString explosivePotion::get_story() {
    return (QObject::tr("The Explosive Potion, a screaming orange with a vortex of fury at its center, constantly boiling and threatening.\nOne throw is enough for all this compressed violence to rock the enemy into an eternal sleep in a cradle of fire and shrapnel."));
}
