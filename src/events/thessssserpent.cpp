#include "thessssserpent.h"
#include "cards/cardfactory.h"

TheSsssserpent::TheSsssserpent(game_action& actions, ironclad* player) {

    manager.unknown_ID = unknownID::the_ssssssserpant;
    manager.unknown_name = tr("The Ssssserpent");
    manager.isEvent = true;

    UnknownNode root;
    root.actions = [](){};
    root.canUse = [](){ return true; };
    root.description = tr("You walk into a room to find a large hole in the ground. As you approach the hole, an enormous serpent creature appears from within.\n\n"
                          "\"Ho hooo! Hello hello! what have we got here? Hello adventurer, I ask a simple question.\n"
                          "The most fulfilling of lives is that in which you can buy anything!\n"
                          "Do you agree?\"");
    root.title = "";


    UnknownNode continue_node;
    continue_node.title = tr("[Continue]");
    continue_node.description = tr("The serpent rears its head and blasts a stream of gold upwards!\n"
                                   "It is amazing and terrifying simultaneously.\n"
                                   "You gather all the gold, thank the snake, and get going.");
    continue_node.actions = [](){};
    continue_node.canUse = [](){ return true; };


    UnknownNode agree_node;
    agree_node.title = tr("[Agree] Gain 175 Gold. Become Cursed - Doubt.");
    agree_node.canUse = [](){ return true; };
    agree_node.description = tr("\"Yeeeeeeesssssssssssessss!\n"
                                "Thissss will all be worthhh it.\n"
                                "..ssSSs..... ss... sssss....!\"");
    agree_node.actions = [player] () {

        player->earn_coin(175);

        abstractCard* doubt = CardFactory::createCard(cardID::doubt);
        player->deck_add(doubt);

    };
    agree_node.next_nodes = {-1};

    UnknownNode disagree_node;
    disagree_node.title = tr("[Disagree] Nothing happens.");
    disagree_node.description = tr("The serpent stares at you with a look of extreme disappointment.");
    disagree_node.actions = [](){};
    disagree_node.canUse = [](){ return true; };
    disagree_node.next_nodes = {-1};

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(agree_node);
    int agreeIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(disagree_node);
    int disagreeIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(continue_node);
    int continueIdx = manager.nodes.size() - 1;

    manager.nodes[rootIdx].next_nodes = {agreeIdx, disagreeIdx, -1};
    manager.nodes[agreeIdx].next_nodes = {continueIdx};
}
