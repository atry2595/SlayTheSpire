#include "demonformpower.h"
#include "powerfactory.h"

demonFormPower::demonFormPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Demon Form"), owner_init, x, 999, 0, true, 0)
{
    description = tr("At the start of your turn, gain %1 Strength.").arg(amount);
}

void demonFormPower::at_turn_start(game_action& actions){
    abstractPower* np = PowerFactory::createPower(powerID::strength, owner, amount);
    owner->add_power(np);
}

QString demonFormPower::generate_description(){
    description = tr("At the start of your turn, gain %1 Strength.").arg(amount);
    return description;
}