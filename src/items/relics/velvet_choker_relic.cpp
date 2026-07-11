#include "velvet_choker_relic.h"
#include "cards/cardfactory.h"
#include "entity/abstractentity.h"
#include "entity/ironclad.h"

velvet_choker_relic::velvet_choker_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Velvet Choker"), owner_init)
{
    description = tr("Gain 1 Energy at the start of your turn. You cannot play more than 6 cards per turn.");
}

QString velvet_choker_relic::generate_description(){
    description = tr("Gain 1 Energy at the start of your turn. You cannot play more than 6 cards per turn.");
    return description;
}

void velvet_choker_relic::at_turn_start(game_action& actions){
    value = 0;
}

void velvet_choker_relic::added_time(game_action& actions){
    ironclad* player = dynamic_cast<ironclad*>(owner);
    if (!player) return;
    player->set_base_energy(player->get_base_energy() + 1);

    play_card_connection = connect(actions.get_event(), &combatEvent::card_played, this,
        [this](playCardInfo& info){
            if (owner == info.owner){
                value++;
                if (value >= 6){
                    ironclad* player = dynamic_cast<ironclad*>(owner);
                    if (!player) return;
                    for (auto item : player->get_combat_deck()) item->set_lock(true);
                }
            }
    });
}
