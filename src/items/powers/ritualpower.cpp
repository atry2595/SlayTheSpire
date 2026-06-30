#include "ritualpower.h"
#include "powerfactory.h"

ritualPower::ritualPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Ritual"), owner_init, x, 999, 0, true, 0)
{
    description = tr("At the start of your/its turn, gain %1 Strength.").arg(amount);
}

void ritualPower::at_turn_start(game_action& actions){
    abstractPower* np = PowerFactory::createPower(powerID::strength, owner, amount);
    owner->add_power(np);
}

QString ritualPower::generate_description(){
    description = tr("At the start of your/its turn, gain %1 Strength.").arg(amount);
    return description;
}