#include "colosseum.h"

#include "cards/cardfactory.h"
#include "items/relics/relicfactory.h"

Colosseum::Colosseum(game_action& actions, ironclad* player)
{
    manager.unknown_ID = unknownID::colosseum;
    manager.unknown_name = tr("The Colosseum");
    manager.isEvent = true;

    UnknownNode root;

    root.actions = [](){};
    root.canUse = [](){ return true; };

    root.title = tr("");

    root.description =
        tr("Thwack!!!\n"
           "..\n"
           "......\n"
           "...\n\n"
           "You were knocked unconscious...");

    UnknownNode continue_node;

    continue_node.actions = [](){};
    continue_node.canUse = [](){ return true; };

    continue_node.title = tr("[Continue]");

    continue_node.description =
        tr("Groggy and with a throbbing head, you awaken to find yourself thrown in the center of a massive stadium with an overflowing audience of Slavers, Cultists, and other denizens of the City!\n\n"
           "An armored giant with a golden crown bellows at you from atop,\n"
           "\"WE NOW BEGIN THE 4200TH COMBAT!!!!\"\n\n"
           "A gate on the opposite side opens...");


    UnknownNode first_fight;

    first_fight.actions =
        []()
    {
        // atry
        // Start combat:
        // Blue Slaver
        // Red Slaver
        // This combat gives NO rewards.
    };

    first_fight.canUse = [](){ return true; };

    first_fight.title =
        tr("[Fight]");

    first_fight.description =
        tr("(The player enters combat with a Blue Slaver and Red Slaver. After ending the fight, more dialogue is presented.)");



    UnknownNode result_node;

    result_node.actions = [](){};

    result_node.canUse = [](){ return true; };

    result_node.title = "";

    result_node.description =
        tr("\"WELL DONE, WEAKLING!\"\n\n"
           "The giant mock claps whilst he riles up the crowd with exaggerated gestures.\n\n"
           "Gold and confetti shower you!\n\n"
           "\"TIME FOR THE REAL CHALLENGE!!\"\n\n"
           "The last battle left a small hole in the Colosseum's wall, you can easily escape through there while everyone is distracted.\n\n"
           "Do you stay and fight?");



    UnknownNode coward_node;

    coward_node.actions =
        []()
    {
        // atry:
        // Leave the event.
        // No reward.
    };

    coward_node.canUse = [](){ return true; };

    coward_node.title =
        tr("[COWARDICE]");

    coward_node.description =
        tr("(No dialogue)");

    coward_node.next_nodes = {-1};


    UnknownNode victory_node;

    victory_node.actions =
        []()
    {
        // atry
        // Start Elite combat:
        // Rewards:
        // 100 Gold
        // 1 Rare Relic
        // 1 Uncommon Relic
        // Card Reward
        // Potion (if applicable)
    };

    victory_node.canUse = [](){ return true; };

    victory_node.title =
        tr("[VICTORY]");

    victory_node.description =
        tr("(No dialogue, the player enters combat with Taskmaster and Gremlin Nob)");

    victory_node.next_nodes = {-1};

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(continue_node);
    int continueIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(first_fight);
    int firstFightIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(result_node);
    int resultIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(coward_node);
    int cowardIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(victory_node);
    int victoryIdx = manager.nodes.size() - 1;


    manager.nodes[rootIdx].next_nodes =
        {
            continueIdx
        };

    manager.nodes[continueIdx].next_nodes =
        {
            firstFightIdx
        };

    manager.nodes[firstFightIdx].next_nodes =
        {
            resultIdx
        };

    manager.nodes[resultIdx].next_nodes =
        {
            cowardIdx,
            victoryIdx
        };
}
