#include "thecleric.h"

TheCleric::TheCleric(game_action& actions, ironclad* player)
{
    manager.unknown_ID = unknownID::the_cleric;
    manager.unknown_name = tr("The Cleric");
    manager.isEvent = true;

    UnknownNode root;
    root.actions = [](){};
    root.canUse = [](){ return true; };

    root.title = "";

    root.description =tr(
        "A strange blue humanoid with a golden helm(?) approaches you with a huge smile.\n\n"
           "\"Hello friend! I am Cleric! Are you interested in my services?!\" the creature shouts, loudly.");

    UnknownNode heal;
    int hhp = (int) player->get_max_hp() / 4;
    heal.title =tr("[Heal] 35 Gold: Heal %1 Max HP.").arg(hhp);

    heal.description =tr(
        "A warm golden light envelops your body and dissipates.\n\n"
        "The creature grins.\n\n"
        "\"Cleric best healer. Have a good day!\"");

    heal.actions = [player, &actions, hhp]()
    {
        player->lose_gold(35);

        healInfo info;
        info.owner = player;
        info.value = hhp;

        actions.heal(info);
    };

    heal.canUse = [player]()
    {
        return player->get_gold() >= 35;
    };

    heal.next_nodes = {-1};

    UnknownNode purify;

    purify.title =tr("[Purify] 50 Gold: Remove a card from your deck.");

    purify.description =tr(
        "A cold blue flame envelops your body and dissipates.\n\n"
           "The creature grins.\n\n"
           "\"Cleric talented. Have a good day!\"");

    purify.actions = [player]()
    {
        player->lose_gold(50);

        std::vector<abstractCard*> pool;

        for (auto item : player->get_deck()) {
            if (item->can_remove_from_deck()) pool.push_back(item);
        }

        abstractCard* selected =
            ironclad::select_card(pool);

        if(selected)
        {
            player->deck_remove(selected);
            delete selected;
        }
    };

    purify.canUse = [player]()
    {
        return player->get_gold() >= 50;
    };

    purify.next_nodes = {-1};


    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(heal);
    int healIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(purify);
    int purifyIdx = manager.nodes.size() - 1;


    manager.nodes[rootIdx].next_nodes =
        {
            healIdx,
            purifyIdx,
            -1
        };
}