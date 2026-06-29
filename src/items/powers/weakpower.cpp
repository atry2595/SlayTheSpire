#include "weakpower.h"

weakPower::weakPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Weak"), owner_init, x, 999, 0, false, 1)
{
    description = tr("Attacks deal 25% less damage for %1 turns.").arg(amount);
}


void weakPower::modify_attack(attackInfo& info) {
    info.damage = int(0.75 * info.damage);
}

void weakPower::at_turn_end(game_action& actions){
    decrease();
}

QString weakPower::generate_description(){
    description = tr("Attacks deal 25% less damage for %1 turns.").arg(amount);
    return description;
}
