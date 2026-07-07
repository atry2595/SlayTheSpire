#include "slavers_collar_relic.h"
#include "cards/abstractcard.h"
#include "items/powers/powerfactory.h"
#include "combat/manageCombat/combat_manager.h"
#include "entity/ironclad.h"

slavers_collar_relic::slavers_collar_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Slaver's Collar"), owner_init)
{
    description = tr("During Boss and Elite combats, gain 1 Energy at the start of your turn.");
}

QString slavers_collar_relic::generate_description(){
    description = tr("During Boss and Elite combats, gain 1 Energy at the start of your turn.");
    return description;
}

void slavers_collar_relic::added_time(game_action& actions){

    combat_start_connection = connect(actions.get_event(), &combatEvent::combat_started, this,
        [this, &actions](combat_manager* info){
            if (info->get_type() == entityType::boss ||
               info->get_type() == entityType::elite ){
                    available = true;
            }
        });

}


void slavers_collar_relic::at_turn_start(game_action& actions){
    if (available){
        ironclad* player = dynamic_cast<ironclad*>(owner);
        if (!player) return;
        player->set_energy(player->get_energy() + 1);
    }
}

void slavers_collar_relic::at_combat_end(game_action& actions){
    available = false;
}