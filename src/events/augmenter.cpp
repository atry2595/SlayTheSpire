#include "augmenter.h"

#include "cards/cardfactory.h"
#include "items/relics/relicfactory.h"
#include "utils/RNG.h"
#include "categories/cards.h"
Augmenter::Augmenter(game_action& actions, ironclad* player)
{
    manager.unknown_ID = unknownID::augmenter;
    manager.unknown_name = tr("Augmenter");
    manager.isEvent = true;

    UnknownNode root;
    root.actions = [](){};
    root.canUse = [](){ return true; };

    root.title = "";

    root.description =
        tr("A man with an eyepatch and a devilish grin strides up to you.\n\n"
           "\"Hey there, stranger. Interested in advancing science? I can make you stronger than any training or blessing. You're gonna need it if you're one of those heroes with a death wish.\"\n\n"
           "\"Whad'ya say?\"");

    UnknownNode testJAX;

    testJAX.title =
        tr("[Test J.A.X.] Get JAXXED.");

    transform.title =
        tr("[Become Test Subject] Transform 2 cards.");

    mutagen.title =
        tr("[Ingest Mutagens] Obtain a special relic.");

    testJAX.description =
        tr(
            "Adds J.A.X. to your deck.\n\n"

            "\"Excellent.\"\n\n"

            "The man hands over a dangerous looking syringe filled with a glowing liquid before skulking off into a shadowy alley."
            );

    testJAX.actions = [player]()
    {
        player->deck_add(CardFactory::createCard(cardID::JAX));
    };

    testJAX.canUse = [](){ return true; };
    testJAX.next_nodes = {-1};


    UnknownNode transform;

    transform.title = tr("[Become Test Subject]");

    transform.description =
        tr(
            "Transform 2 cards.\n\n"

            "\"Marvelous.\"\n\n"

            "You quaff the mysterious substance. Immediately, you are invigorated and feel your muscle fibers twitch."
            );

    transform.actions = [player]()
    {
        std::vector<cardID> pool = non_rare_cards;
        pool.insert(pool.end(), rare_cards.begin(), rare_cards.end());

        std::vector<abstractCard*> selectable;

        for (auto card : player->get_deck())
        {
            if (card->get_card_type() != CardType::curse &&
                card->get_card_type() != CardType::status)
            {
                selectable.push_back(card);
            }
        }

        if (selectable.empty())
            return;


        abstractCard* first = ironclad::select_card(selectable);

        cardID randomCard1 = RNG::instance().choice(pool);

        player->deck_remove(first);
        delete first;
        player->deck_add(CardFactory::createCard(randomCard1));


        selectable.clear();

        for (auto card : player->get_deck())
        {
            if (card->get_card_type() != CardType::curse &&
                card->get_card_type() != CardType::status)
            {
                selectable.push_back(card);
            }
        }

        if (selectable.empty())
            return;

        abstractCard* second = ironclad::select_card(selectable);

        cardID randomCard2 = RNG::instance().choice(pool);

        player->deck_remove(second);
        delete second;
        player->deck_add(CardFactory::createCard(randomCard2));
    };
    transform.canUse = [](){ return true; };
    transform.next_nodes = {-1};

    UnknownNode mutagen;

    mutagen.title = tr("[Ingest Mutagens]");

    mutagen.description =
        tr(
            "Obtain Mutagenic Strength.\n\n"

            "\"Superb.\"\n\n"

            "The man injects you with three unknown substances and pulls out a notepad. As you begin to feel light-headed, he starts to frantically write down notes.\n\n"

            "Losing track of time completely, by the time you regain your senses, the shady character has disappeared."
            );

    mutagen.actions = [player, &actions]()
    {
        abstractRelic* relic =
            RelicFactory::createRelic(
                relicID::mutagenic_strength,
                player);

        player->add_relic(actions, relic);
    };

    mutagen.canUse = [](){ return true; };
    mutagen.next_nodes = {-1};

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(testJAX);
    int jaxIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(transform);
    int transformIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(mutagen);
    int mutagenIdx = manager.nodes.size() - 1;

    manager.nodes[rootIdx].next_nodes =
        {
            jaxIdx,
            transformIdx,
            mutagenIdx,
            -1
        };
}