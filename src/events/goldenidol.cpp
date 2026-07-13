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
        "You come across an inconspicuous pedestal with a shining gold idol sitting peacefully atop. It looks incredibly valuable.\n\n"
        "You sure don't see any traps nearby."
        );

    UnknownNode take_node;
    take_node.title = tr("[Take]");
    take_node.description = tr(
        "As you grab the Idol and stow it away, a giant boulder smashes through the ceiling into the ground next to you.\n\n"
        "You realize that the floor is slanted downwards as the boulder starts to roll towards you."
        );

    take_node.actions = [player, &actions]()
    {
        Q_UNUSED(player);
        Q_UNUSED(actions);

        // +++؟
    };

    take_node.canUse = [](){ return true; };


    UnknownNode outrun_node;
    outrun_node.title = tr("[Outrun]");
    outrun_node.description = tr(
        "RUUUUUUUUUUN!\n\n"
        "You barely leap into a side passageway as the boulder rushes by.\n"
        "Unfortunately it feels like you sprained something however."
        );

    outrun_node.actions = [player]()
    {
        Q_UNUSED(player);

        // +++؟
    };

    outrun_node.canUse = [](){ return true; };
    outrun_node.next_nodes = {-1};

    UnknownNode smash_node;
    smash_node.title = tr("[Smash]");
    smash_node.description = tr(
        "You throw yourself at the boulder with everything you have. When the dust clears, you can make a safe way out."
        );

    smash_node.actions = [player]()
    {
        Q_UNUSED(player);

        // +++؟
    };

    smash_node.canUse = [](){ return true; };
    smash_node.next_nodes = {-1};

    UnknownNode hide_node;
    hide_node.title = tr("[Hide]");
    hide_node.description = tr(
        "SQUISH!\n"
        "The boulder flattens you a little as it passes by, but otherwise you can get out of here."
        );

    hide_node.actions = [player]()
    {
        Q_UNUSED(player);

        // +++؟
    };

    hide_node.canUse = [](){ return true; };
    hide_node.next_nodes = {-1};

    UnknownNode leave_node;
    leave_node.title = tr("[Leave]");
    leave_node.description = tr(
        "If there was ever an obvious trap, this would be it.\n"
        "You decide not to interfere with objects placed upon pedestals."
        );

    leave_node.actions = [](){};

    leave_node.canUse = [](){ return true; };
    leave_node.next_nodes = {-1};

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(take_node);
    int takeIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(outrun_node);
    int outrunIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(smash_node);
    int smashIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(hide_node);
    int hideIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(leave_node);
    int leaveIdx = manager.nodes.size() - 1;

    manager.nodes[rootIdx].next_nodes =
        {
            takeIdx,
            leaveIdx
        };

    manager.nodes[takeIdx].next_nodes =
        {
            outrunIdx,
            smashIdx,
            hideIdx
        };
}