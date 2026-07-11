#include "oddly_smooth_stone_relic.h"
#include "items/powers/powerfactory.h"

oddly_smooth_stone_relic::oddly_smooth_stone_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Oddly Smooth Stone"), owner_init)
{
    description = tr("At the start of each combat, gain 1 Dexterity.");
}

QString oddly_smooth_stone_relic::generate_description(){
    description = tr("At the start of each combat, gain 1 Dexterity.");
    return description;
}


void oddly_smooth_stone_relic::at_combat_start(game_action& actions){
    abstractPower* np = PowerFactory::createPower(powerID::dexterity, owner, 1);
    owner->add_power(actions, np);
}