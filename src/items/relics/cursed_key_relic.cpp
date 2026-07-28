#include "cursed_key_relic.h"
#include "entity/abstractentity.h"
#include "cards/cardfactory.h"
#include "utils/RNG.h"
#include "entity/ironclad.h"

cursed_key_relic::cursed_key_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Cursed Key"), owner_init)
{
    description = tr("Gain 1 Energy at the start of your turn. Whenever you open a non-Boss chest, obtain a Curse.");
}

QString cursed_key_relic::generate_description(){
    description = tr("Gain 1 Energy at the start of your turn. Whenever you open a non-Boss chest, obtain a Curse.");
    return description;
}


void cursed_key_relic::added_time(game_action& actions){
    open_chest_connection = connect(actions.get_event(), &combatEvent::chestOpened, this, [=](){
        auto pool = curse_cards;
        auto crd = CardFactory::createCard(RNG::instance().choice(pool));
        auto player = dynamic_cast<ironclad*>(owner);
        player->deck_add(crd);
    });
}

QString cursed_key_relic::get_story() {
    return (QObject::tr("The Cursed Key opens every door, but a muffled laugh echoes from every keyhole.\nThe traveler empties chest after chest, unaware that with every turn, this key tightens a curse they've never read."));
}
