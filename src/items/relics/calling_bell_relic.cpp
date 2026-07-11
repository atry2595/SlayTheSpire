#include "calling_bell_relic.h"
#include "entity/abstractentity.h"
#include "cards/cardfactory.h"
#include "utils/RNG.h"
#include "entity/ironclad.h"
#include "relicfactory.h"


calling_bell_relic::calling_bell_relic(abstractEntity* owner_init)
    :abstractRelic(tr("Calling Bell"), owner_init)
{
    description = tr("Upon pickup, obtain a unique Curse and 3 relics.");
}

QString calling_bell_relic::generate_description(){
    description = tr("Upon pickup, obtain a unique Curse and 3 relics.");
    return description;
}


void calling_bell_relic::added_time(game_action& actions){
    ironclad* player = dynamic_cast<ironclad*>(owner);
    if (!player) return;

    abstractCard* nc = CardFactory::createCard(cardID::curse_of_the_bell);
    player->deck_add(nc);

    RNG& rng = RNG::instance();

    std::vector<relicID> rares = rare_relic;
    std::vector<relicID> uncommons = uncommon_relic;
    std::vector<relicID> commons = common_relic;

    rng.shuffle(rares);
    rng.shuffle(uncommons);
    rng.shuffle(commons);

    std::vector<relicID> selected;

    // ++++++++++++by Ai++++++++++++++++

    auto take_from_pool = [&](std::vector<relicID>& pool) -> bool {
        for (auto item : pool) {

            if (owner->get_spec_relic(item) != nullptr)
                continue;

            if (std::find(selected.begin(), selected.end(), item) != selected.end())
                continue;

            selected.push_back(item);
            return true;
        }
        return false;
    };

    // -------- First Relic --------
    if (!take_from_pool(rares))
        if (!take_from_pool(uncommons))
            take_from_pool(commons);

    // -------- Second Relic --------
    if (!take_from_pool(uncommons))
        take_from_pool(commons);

    // -------- Third Relic --------
    take_from_pool(commons);

    for (auto item : selected){
        abstractRelic* nr = RelicFactory::createRelic(item, owner);
        owner->add_relic(actions, nr);
    }
}
