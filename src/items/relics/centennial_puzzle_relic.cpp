#include "centennial_puzzle_relic.h"
#include "entity/ironclad.h"

centennial_puzzle_relic::centennial_puzzle_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Centennial Puzzle"), owner_init)
{
    description = tr("The first time you lose HP each combat, draw 3 cards.");
}

QString centennial_puzzle_relic::generate_description(){
    description = tr("The first time you lose HP each combat, draw 3 cards.");
    return description;
}


void centennial_puzzle_relic::at_combat_start(game_action& actions){
    active = true;
}

void centennial_puzzle_relic::damage_applied(game_action& actions){
    if (active){
        active = false;
        ironclad* player = dynamic_cast<ironclad*>(owner);
        if (!player) return;
        for (int i = 0 ; i < 3; i++){
            player->draw_card();
        }
    }
}

QString centennial_puzzle_relic::get_story() {
    return (QObject::tr("The Centennial Puzzle, a box unopened for a century, clicks and turns one lock with each battle fought.\nThe traveler doesn't know what happens when all the pieces fall into place, but every click resonates a promise in their bones: something ancient is about to wake up."));
}
