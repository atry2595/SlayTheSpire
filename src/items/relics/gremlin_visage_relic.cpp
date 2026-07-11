#include "gremlin_visage_relic.h"
#include "items/powers/powerfactory.h"
#include "entity/abstractentity.h"

gremlin_visage_relic::gremlin_visage_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Gremlin Visage"), owner_init)
{
    description = tr("Start each combat with 1 Weak.");
}

QString gremlin_visage_relic::generate_description(){
    description = tr("Start each combat with 1 Weak.");
    return description;
}


void gremlin_visage_relic::at_combat_start(game_action& actions){
    abstractPower* np = PowerFactory::createPower(powerID::weak, owner, 1);
    owner->add_power(actions, np);
}
