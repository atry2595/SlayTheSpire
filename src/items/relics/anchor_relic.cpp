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

QString anchor_relic::get_story() {
    return (QObject::tr("The Anchor at the bottom of the pocket remembers the sea and the storm, but now it's just a weight to stand firm.\nThe traveler carries it not for a ship, but to block life's incoming blows, because sometimes the heaviest burdens become the safest shields."));
}
