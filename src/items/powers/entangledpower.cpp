#include "entangledpower.h"
#include "entity/ironclad.h"
#include "combat/blocking_info.h"
#include "cards/abstractcard.h"

entangledPower::entangledPower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Entangled"), owner_init, x, 1, 0, false, 0)
{
    description = tr("You may not play any Attacks this turn.").arg(amount);
}


QString entangledPower::generate_description(){
    description = tr("You may not play any Attacks this turn.").arg(amount);
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
        [this, &player](abstractCard* card, PileType from, PileType to){
        if (from == PileType::none && card->get_card_type() == CardType::attack){
            card->set_lock(true);
        }
    });

}
