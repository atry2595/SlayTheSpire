#include "entangledpower.h"
#include "entity/ironclad.h"
#include "combat/blocking_info.h"
#include "cards/abstractcard.h"

entangledPower::entangledPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Entangled"), owner_init, x, 1, 0, false, 0)
{
    description = tr("You may not play any Attacks this turn.");
}


QString entangledPower::generate_description(){
    description = tr("You may not play any Attacks this turn.");
    return description;
}

void entangledPower::added_time(game_action& actions) {
    ironclad* player = dynamic_cast<ironclad*>(owner);
    for (auto& item : player->get_combat_deck()){
        if (item->get_card_type() == CardType::attack){
            item->set_lock(true);
        }
    }

    add_card_connection = connect(actions.get_event(), &combatEvent::card_moved, this,
        [this, &player](playCardInfo& card, PileType from, PileType to){
        if (from == PileType::none && card.card->get_card_type() == CardType::attack && owner == card.owner){
            card.card->set_lock(true);
        }
    });

}


void entangledPower::at_turn_end(game_action&) {
    disconnect(add_card_connection);
    decrease(amount);
}