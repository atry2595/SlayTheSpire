#include "horn_cleat_relic.h"

horn_cleat_relic::horn_cleat_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Horn Cleat"), owner_init)
{
    description = tr("At the start of your 2nd turn, gain 14 Block.");
}

QString horn_cleat_relic::generate_description(){
    description = tr("At the start of your 2nd turn, gain 14 Block.");
    return description;
}


void horn_cleat_relic::at_turn_start(game_action& actions){
    turn++;
    if (turn == 2) {
        blockingInfo inf;
        inf.block = 14;
        inf.affected_by_other = false;
        inf.owner = owner;
        actions.apply_block(inf);
    }
}

void horn_cleat_relic::at_combat_end(game_action& actions){
    turn = 0;
}