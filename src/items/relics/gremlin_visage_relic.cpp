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

QString gremlin_visage_relic::get_story() {
    return (QObject::tr("The Gremlin Visage, an ugly, ridiculous mask with a frozen sneer that even death can't wipe off.\nThe traveler laughs at the absurdity of dying through this grotesque face, and right at the brink of collapse, stands back up—as if mocking mortality is itself a form of survival."));
}
