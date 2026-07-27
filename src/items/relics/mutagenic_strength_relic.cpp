#include "mutagenic_strength_relic.h"
#include "items/powers/powerfactory.h"

mutagenic_strength_relic::mutagenic_strength_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Mutagenic Strength"), owner_init)
{
    description = tr("Start each combat with 3 Strength. At the end of your first turn, lose 3 Strength.");
}

QString mutagenic_strength_relic::generate_description(){
    description = tr("Start each combat with 3 Strength. At the end of your first turn, lose 3 Strength.");
    return description;
}


void mutagenic_strength_relic::at_combat_start(game_action& actions){
    abstractPower* np = PowerFactory::createPower(powerID::strength, owner, 3);
    owner->add_power(actions, np);
    used = true;
}


void mutagenic_strength_relic::at_turn_end(game_action& actions)
{
    if (used){
        abstractPower* np = PowerFactory::createPower(powerID::strength, owner, -3);
        owner->add_power(actions, np);
        used = false;
    }
}

QString mutagenic_strength_relic::get_story() {
    return (QObject::tr("Mutagenic Strength, a liquid shock surging through veins, swelling muscles with a biological fury.\nThe traveler becomes a temporary monster in the first moment of battle, but this potent poison quickly dissolves in the blood, leaving only the fading memory of an inner giant."));
}
