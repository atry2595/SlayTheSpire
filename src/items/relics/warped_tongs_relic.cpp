#include "warped_tongs_relic.h"
#include "entity/ironclad.h"
#include "utils/RNG.h"

warped_tongs_relic::warped_tongs_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Warped Tongs"), owner_init)
{
    description = tr("At the start of your turn, Upgrade a random card in your hand for the rest of combat.");
}

QString warped_tongs_relic::generate_description(){
    description = tr("At the start of your turn, Upgrade a random card in your hand for the rest of combat.");
    return description;
}


void warped_tongs_relic::at_turn_start(game_action&)
{
    ironclad* player = dynamic_cast<ironclad*>(owner);
    if (!player)
        return;

    auto& hand = player->get_hand_pile();
    if (hand.empty())
        return;

    abstractCard* card = RNG::instance().choice(hand);
    card->upgrade();
}

QString warped_tongs_relic::get_story() {
    return (QObject::tr("The Warped Tongs, their metal bearing a rainbow of scars from the heat of a thousand deformations.\nThe traveler entrusts their cards to these tongs and receives them back bent and twisted—yet in this crookedness lies a power never found in straight lines."));
}
