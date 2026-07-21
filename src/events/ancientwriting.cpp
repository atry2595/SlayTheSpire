#include "ancientwriting.h"

AncientWriting::AncientWriting(game_action& actions, ironclad* player)
{
    Q_UNUSED(actions);

    manager.unknown_ID = unknownID::ancient_writing;
    manager.unknown_name = tr("Ancient Writing");
    manager.isEvent = true;

    UnknownNode root;

    root.actions = [](){};
    root.canUse = [](){ return true; };

    root.title = "";

    root.description =tr(
        "Scaling the city, you notice a wall covered in the writing of Ancients. "
        "As you try to wrap your head around what the puzzling symbols and glyphs could mean, "
        "the writing begins to glow.\n\n"
        "Suddenly, the message becomes clear...");

    UnknownNode elegance;

    elegance.title =tr("[Elegance] Remove a card from your deck.");

    elegance.description =tr(
        "The answer was elegance.\n"
        "Of course.");

    elegance.actions = [=, &actions]()
    {
        std::vector<abstractCard*> selectable;

        for (auto card : player->get_deck())
        {
            if (card->can_remove_from_deck())
                selectable.push_back(card);
        }

        if (selectable.empty())
            return;

        emit actions.get_event()->selectCard(selectable);
        connect(actions.get_event(), &combatEvent::cardSelected, this, [=](abstractCard* card){

            if (card){
                player->deck_remove(card);
                delete card;
            }

        });

    };

    elegance.canUse = [](){ return true; };
    elegance.next_nodes = {-1};

    UnknownNode simplicity;

    simplicity.title =tr(
        "[Simplicity] Upgrade all Strikes and Defends.");

    simplicity.description =tr(
        "The truth is always simple.");

    simplicity.actions = [player]()
    {
        for (auto card : player->get_deck())
        {
            if ((card->get_card_id() == cardID::strike || card->get_card_id() == cardID::defend) && !card->get_upgraded())
            {
                card->base_upgrade();
            }
        }
    };

    simplicity.canUse = [](){ return true; };
    simplicity.next_nodes = {-1};

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(elegance);
    int eleganceIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(simplicity);
    int simplicityIdx = manager.nodes.size() - 1;

    manager.nodes[rootIdx].next_nodes =
        {
            eleganceIdx,
            simplicityIdx
        };
}