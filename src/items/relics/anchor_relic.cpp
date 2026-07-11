#include "anchor_relic.h"
#include "cards/abstractcard.h"
#include "items/powers/powerfactory.h"

anchor_relic::anchor_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Anchor"), owner_init)
{
    description = tr("Start each combat with 10 Block.");
}

QString anchor_relic::generate_description(){
    description = tr("Start each combat with 10 Block.");
    return description;
}


void anchor_relic::at_combat_start(game_action& actions){
    blockingInfo inf;
    inf.block = value;
    inf.affected_by_other = false;
    inf.owner = owner;
    actions.apply_block(inf);
}