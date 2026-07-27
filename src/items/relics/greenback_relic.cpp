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

QString greenback_relic::get_story() {
    return (QObject::tr("The Greenback, a crisp and fresh banknote, keeps hope's lantern burning amidst the Spire's smoke and blood.As long as it rests in the traveler's pocket, an invisible armor of confidence wraps around them—as if money truly can be a shield."));
}
