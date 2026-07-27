#include "mark_of_pain_relic.h"
#include "cards/cardfactory.h"
#include "entity/abstractentity.h"
#include "entity/ironclad.h"

mark_of_pain_relic::mark_of_pain_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Mark Of Pain"), owner_init)
{
    description = tr("Gain 1 Energy at the start of your turn. At the start of combat, add 2 Wounds into your draw pile.");
}

QString mark_of_pain_relic::generate_description(){
    description = tr("Gain 1 Energy at the start of your turn. At the start of combat, add 2 Wounds into your draw pile.");
    return description;
}

void mark_of_pain_relic::at_combat_start(game_action& actions){
    ironclad* player = dynamic_cast<ironclad*>(owner);
    if (!player) return;
    abstractCard* nc1 = CardFactory::createCard(cardID::wound);
    abstractCard* nc2 = CardFactory::createCard(cardID::wound);
    player->draw_pile_add(nc1);
    player->draw_pile_add(nc2);

}

void mark_of_pain_relic::added_time(game_action& actions){
    ironclad* player = dynamic_cast<ironclad*>(owner);
    if (!player) return;
    player->set_base_energy(player->get_base_energy() + 1);
}

QString mark_of_pain_relic::get_story() {
    return (QObject::tr("The Mark of Pain is a wound the traveler carved into their own flesh, a signature made of suffering.\nYet from this self-inflicted gash, a fury is born that no blade earns without a blood price—as if some powers are only bought with a piece of yourself."));
}
