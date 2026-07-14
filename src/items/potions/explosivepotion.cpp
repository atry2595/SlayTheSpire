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