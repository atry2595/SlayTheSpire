#include "goldenidol.h"

GoldenIdol::GoldenIdol(game_action& actions, ironclad* player)
{
    Q_UNUSED(actions);
    Q_UNUSED(player);

    manager.unknown_ID = unknownID::golden_idol;
    manager.unknown_name = tr("Golden Idol");
    manager.isEvent = true;


    UnknownNode root;
    root.actions = [](){};
    root.canUse = [](){ return true; };
    root.title = "";
    root.description = tr(
        "Before you is an elaborate shrine to a forgotten spirit.\n\n"
        "In the center of the shrine sits a Golden Idol, glowing in the light."
        );


    UnknownNode take_node;
    take_node.title = tr("[Take] Obtain the Golden Idol. Lose 5 Max HP.");
    take_node.description = tr(
        "You reach for the Golden Idol.\n\n"
        "The shrine trembles as you pry it free."
        );

    take_node.actions = [player, &actions]()
    {
        Q_UNUSED(player);
        Q_UNUSED(actions);

        // ++++?
    };

    take_node.canUse = [](){ return true; };
    take_node.next_nodes = {-1};

    UnknownNode leave_node;
    leave_node.title = tr("[Leave]");
    leave_node.description = tr(
        "You decide it is better not to disturb the shrine."
        );

    leave_node.actions = [](){};

    leave_node.canUse = [](){ return true; };
    leave_node.next_nodes = {-1};

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(take_node);
    int takeIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(leave_node);
    int leaveIdx = manager.nodes.size() - 1;

    manager.nodes[rootIdx].next_nodes =
        {
            takeIdx,
            leaveIdx
        };
}