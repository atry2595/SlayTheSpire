#include "augmenter.h"

#include "cards/cardfactory.h"
#include "items/relics/relicfactory.h"
#include "entity/ironclad.h"
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



    testJAX.description =
        tr(
            "\"Excellent.\"\n\n"
            "The man hands over a dangerous looking syringe filled with a glowing liquid before skulking off into a shadowy alleyway."
            );

    testJAX.actions = [player]()
    {
        player->deck_add(CardFactory::createCard(cardID::JAX));
    };

    testJAX.canUse = [](){ return true; };
    testJAX.next_nodes = {-1};


    UnknownNode transform;

    transform.title = tr("[Become Test Subject] Transform 2 cards.");

    transform.description =
        tr(
            "\"Marvelous.\"\n\n"
            "You quaff the mysterious substance. Immediately, you are invigorated and feel your muscle fibers twitch."
            );

    transform.actions = [eve = actions.get_event(), player]()
    {

        if (player->get_deck().empty()) return;
        emit eve->selectCard(player->get_deck());
        auto conn = std::make_shared<QMetaObject::Connection>();
        *conn = connect(eve, &combatEvent::cardSelected, eve, [=](abstractCard* card){

            if (card){
                abstractCard* rand1 = ironclad::transformCard(card);

                player->deck_remove(card);
                player->deck_add(rand1);
            }

            if (player->get_deck().empty()) return;
            emit eve->selectCard(player->get_deck());
            auto conn2 = std::make_shared<QMetaObject::Connection>();
            *conn2 = connect(eve, &combatEvent::cardSelected, eve, [=](abstractCard* card){

                if (card){
                    abstractCard* rand2 = ironclad::transformCard(card);

                    player->deck_remove(card);
                    player->deck_add(rand2);
                }
                disconnect(*conn2);

            });
            disconnect(*conn);
        });

    };
    transform.canUse = [](){ return true; };
    transform.next_nodes = {-1};

    UnknownNode mutagen;

    mutagen.title = tr("[Ingest Mutagens] Obtain a special relic.");

    mutagen.description =
        tr(

            "\"Superb.\"\n\n"

            "The man injects you with three unknown substances and pulls out a notepad. As you begin to feel light-headed, he starts to frantically write down notes.\n\n"

            "Losing track of time completely, by the time you regain your senses, the shady character has disappeared."
            );

    mutagen.actions = [player, eve = actions.get_event()]()
    {
        abstractRelic* relic =
            RelicFactory::createRelic(
                relicID::mutagenic_strength,
                player);

        game_action actions(eve);
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