#include "goldenshrine.h"

#include "cards/cardfactory.h"

GoldenShrine::GoldenShrine(game_action& actions, ironclad* player)
{
    Q_UNUSED(actions);

    manager.unknown_ID = unknownID::golden_shrine;
    manager.unknown_name = tr("Golden Shrine");
    manager.isEvent = true;

    UnknownNode root;

    root.actions = [](){};

    root.canUse = [](){ return true; };

    root.title = "";

    root.description =tr("Before you lies an elaborate shrine to an ancient spirit.");

    UnknownNode pray;

    pray.title =tr("[Pray] Gain 100 Gold.");

    pray.description =tr("As your hand touches the shrine, gold rains from the ceiling showering you in riches.");

    pray.actions = [player]()
    {
        player->earn_coin(100);
    };

    pray.canUse = [](){ return true; };

    pray.next_nodes = {-1};

    UnknownNode desecrate;

    desecrate.title =tr("[Desecrate] Gain 275 Gold.\n"
                         "           Become Cursed - Regret.");

    desecrate.description =tr(
        "Each time you strike the shrine, gold pours forth again and again!\n\n"
        "As you pocket the riches, something weighs heavily on you.");

    desecrate.actions = [player]()
    {
        player->earn_coin(275);

        abstractCard* curse =CardFactory::createCard(cardID::regret);

        player->deck_add(curse);
    };

    desecrate.canUse = [](){ return true; };

    desecrate.next_nodes = {-1};


    //------------------------------------------------------------

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(pray);
    int prayIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(desecrate);
    int desecrateIdx = manager.nodes.size() - 1;


    manager.nodes[rootIdx].next_nodes =
        {
            prayIdx,
            desecrateIdx,
            -1
        };
}