#include "greenback_relic.h"
#include "cards/abstractcard.h"
#include "items/powers/powerfactory.h"

greenback_relic::greenback_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Greenback"), owner_init)
{
    description = tr("If you end your turn without Block, gain 6 Block.");
}

QString greenback_relic::generate_description(){
    description = tr("If you end your turn without Block, gain 6 Block.");
    return description;
}


void greenback_relic::at_turn_end(game_action& actions){
    if (owner->get_block() == 0){
        blockingInfo inf;
        inf.block = value;
        inf.affected_by_other = false;
        inf.owner = owner;
        actions.apply_block(inf);
    }
}