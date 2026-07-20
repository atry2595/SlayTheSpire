#include "captains_wheel_relic.h"

captains_wheel_relic::captains_wheel_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Captain's Wheel"), owner_init)
{
    description = tr("At the start of your 3rd turn, gain 18 Block.");
}

QString captains_wheel_relic::generate_description(){
    description = tr("At the start of your 3rd turn, gain 18 Block.");
    return description;
}


void captains_wheel_relic::at_turn_start(game_action& actions){
    turn++;
    if (turn == 3) {
        blockingInfo inf;
        inf.block = 18;
        inf.affected_by_other = false;
        inf.owner = owner;
        actions.apply_block(inf);
    }
}

void captains_wheel_relic::at_combat_end(game_action& actions){
    turn = 0;
}

QString captains_wheel_relic::get_story() {
    return (QObject::tr("The Captain's Wheel, its wood cracked but still firm, keeps the dream of open seas alive in the Spire's stone prison.\nTurning it, the traveler steers not a ship but their own quickening pulse, as if fate itself is the most steerable of vessels."));
}
