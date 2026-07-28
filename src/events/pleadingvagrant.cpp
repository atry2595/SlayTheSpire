#include "pleadingvagrant.h"

#include "items/relics/relicfactory.h"
#include "cards/cardfactory.h"
#include "categories/relics.h"
#include "utils/RNG.h"

PleadingVagrant::PleadingVagrant(game_action& actions, ironclad* player)
{
    manager.unknown_ID = unknownID::pleading_vagrant;
    manager.unknown_name = tr("Pleading Vagrant");
    manager.isEvent = true;

    UnknownNode root;

    root.actions = [](){};
    root.canUse = [](){ return true; };

    root.title = "";

    root.description =tr(
        "While sneaking past a group of shrouded figures, one of them approaches you.\n"
        "\"Got anything for me friend? Please... maybe some Coin?\"\n"
        "\"I just need somewhere to stay, I have treasures I can trade...\"\n\n"
        "He seems delusional, but harmless.");

    UnknownNode offer;

    offer.title =tr("[Offer Gold] 85 Gold: Obtain a Relic.");

    offer.description =tr("\"Oh yes, yes! Here here, a fair trade!\"");

    offer.actions = [player, eve = actions.get_event()]()
    {
        game_action actions(eve);

        player->lose_gold(85);

        std::vector<relicID> relicPool = common_relic;

        relicPool.insert(relicPool.end(),uncommon_relic.begin(),uncommon_relic.end());

        relicPool.insert(relicPool.end(),rare_relic.begin(),rare_relic.end());

        relicID id =RNG::instance().choice(relicPool);

        abstractRelic* relic =RelicFactory::createRelic(id, player);

        player->add_relic(actions, relic);
    };

    offer.canUse = [player]()
    {
        return player->get_gold() >= 85;
    };

    offer.next_nodes = {-1};

    UnknownNode rob;

    rob.title =tr("[Rob] Obtain a Relic. Become Cursed - Shame.");

    rob.description =tr(
        "You snatch the precious relic from his clutches and walk away.\n\n"
        "From behind you hear,\n"
        "\"Have you no shame? HAVE YOU NO SHAAAAAME?!\"\n\n"
        "You have some shame.");

    rob.actions = [player, eve = actions.get_event()]()
    {
        game_action actions(eve);

        std::vector<relicID> relicPool = common_relic;

        relicPool.insert(relicPool.end(),uncommon_relic.begin(),uncommon_relic.end());

        relicPool.insert(relicPool.end(),rare_relic.begin(),rare_relic.end());

        relicID id =RNG::instance().choice(relicPool);

        abstractRelic* relic =RelicFactory::createRelic(id, player);

        player->add_relic(actions, relic);

        player->deck_add(CardFactory::createCard(cardID::shame));
    };

    rob.canUse = [](){ return true; };

    rob.next_nodes = {-1};

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(offer);
    int offerIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(rob);
    int robIdx = manager.nodes.size() - 1;

    manager.nodes[rootIdx].next_nodes =
        {
            offerIdx,
            robIdx,
            -1
        };
}