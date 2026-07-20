#include "firepotion.h"
#include "combat/attack_info.h"

firePotion::firePotion(abstractEntity* owner_init)
    :abstractPotion(tr("Fire Potion"), tr("Deal 20 damage to target enemy."), owner_init)
{}

void firePotion::play(playInfo& info){

    attackInfo a;
    a.attacker = nullptr; //without is affected by others
    a.target_list = info.target_list;
    a.damage = amount;
    a.attack_type = attackType::potion;

    info.actions.attack(a);
}

QString firePotion::get_story() {
    return (QObject::tr("The Fire Potion dances in its bottle, its flames restless and furious, as if it cannot bear imprisonment.\nThe moment it's thrown, all that caged fury is released, embracing the enemy in a blaze that has been waiting for this moment."));
}
