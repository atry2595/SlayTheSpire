#include "vajra_relic.h"
#include "items/powers/powerfactory.h"

vajra_relic::vajra_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Vajra"), owner_init)
{
    description = tr("At the start of each combat, gain 1 Strength.");
}

QString vajra_relic::generate_description(){
    description = tr("At the start of each combat, gain 1 Strength.");
    return description;
}


void vajra_relic::at_combat_start(game_action& actions){
    abstractPower* np = PowerFactory::createPower(powerID::strength, owner, 1);
    owner->add_power(actions, np);
}