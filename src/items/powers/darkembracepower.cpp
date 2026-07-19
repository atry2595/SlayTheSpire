#include "darkembracepower.h"
#include "cards/abstractcard.h"
#include "entity/ironclad.h"

darkEmbracePower::darkEmbracePower(abstractEntity* owner_init, int x)
    : abstractPower(tr("Dark Embrace"), owner_init, x, 999, 0, true, 1)
{
    description = tr("Whenever you Exhaust a card, draw %1 card.").arg(amount);
}


QString darkEmbracePower::generate_description(){
    description = tr("Whenever you Exhaust a card, draw %1 card.").arg(amount);
    return description;
}

void darkEmbracePower::added_time(game_action& actions) {
    exhaust_card_connection = connect(actions.get_event(), &combatEvent::card_moved, this,
        [this, &actions](playCardInfo& card, PileType from, PileType to) {
            if (to == PileType::exhaust && owner == card.owner && !card.card->get_ethereal()){
                ironclad* player = dynamic_cast<ironclad*>(owner);
                player->draw_card();
            }
        });
}