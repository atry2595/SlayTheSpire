#include "firepotion.h"
#include "combat/attack_info.h"

firePotion::firePotion(abstractEntity* owner_init)
    :abstractPotion(tr("Fire Potion"), tr("Deal 20 damage to target enemy."), owner_init)
{}

void firePotion::play(playInfo& info){

    attackInfo a;
    a.attacker = nullptr; //without is affected by others
    a.target_list = info.target_list;
    a.damage = 20;

    info.actions.attack(a);
}