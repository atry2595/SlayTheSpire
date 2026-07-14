#include "joust.h"
#include "utils/RNG.h"
#include "items/relics/relicfactory.h"
#include "cards/cardfactory.h"

Joust::Joust(game_action& actions, ironclad* player) {

    manager.unknown_ID = unknownID::the_joust;
    manager.unknown_name = tr("The Joust");
    manager.isEvent = true;

    //-------------------------------------------------------------------------------

    UnknownNode root;
    root.title = "";
    root.description = tr("As you make your way through the large buildings you come across a long narrow bridge and spot knights on either side, facing one another.\n"
                          "You approach...\n"
                          "\"HALT!\"\n\n"
                          "A knight forcefully gestures you to stop with its giant lance.");
    root.canUse = []() { return true; };
    root.actions = []() {};
    //-------------------------------------------------------------------------------

    UnknownNode continue_node;
    continue_node.title = tr("[Continue]");
    continue_node.description = tr("\"Today is the day I must settle the score with the murderer of my beloved pet, Noodles. Until then, you may not pass.\n\n"
                                   "Fellow witness, why don't you bet on who you think will emerge victorious?\""
                                   "\nIf you win, obtain a relic - red mask\n"
                                   "If you lose, become cursed - writhe");

    continue_node.canUse = []() { return true; };
    continue_node.actions = []() {};

    //-------------------------------------------------------------------------------

    bool murder_win = RNG::instance().chance(0.6);

    //-------------------------------------------------------------------------------
    UnknownNode bet_murderer;
    bet_murderer.title = tr("[Murderer]");
    bet_murderer.next_nodes = {-1};
    bet_murderer.canUse = [player]() {
        return true;
    };
    if (murder_win) {
        bet_murderer.description = tr("You win the bet. Unsure what to think, you grab your winnings and leave.");
        bet_murderer.actions = [player, &actions] (){
            auto rlc = RelicFactory::createRelic(relicID::red_mask, player);
            player->add_relic(actions, rlc);
        };
    }
    else {
        bet_murderer.description = tr("You lost the bet, but at least you weren't gouged by a lance.");
        bet_murderer.actions = [player]() {
            auto card = CardFactory::createCard(cardID::writhe);
            player->deck_add(card);
        };
    }

    //-------------------------------------------------------------------------------
    UnknownNode bet_owner;
    bet_owner.title = tr("[Owner]");
    bet_owner.next_nodes = {-1};
    bet_owner.canUse = [player]() {
        return true;
    };
    if (!murder_win) {
        bet_owner.description = tr("You win the bet. Unsure what to think, you grab your winnings and leave.");
        bet_owner.actions = [player, &actions] (){
            auto rlc = RelicFactory::createRelic(relicID::red_mask, player);
            player->add_relic(actions, rlc);
        };
    }
    else {
        bet_owner.description = tr("You lost the bet, but at least you weren't gouged by a lance.");
        bet_owner.actions = [player]() {
            auto card = CardFactory::createCard(cardID::writhe);
            player->deck_add(card);
        };
    }


    //-------------------------------------------------------------------------------

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(continue_node);
    int continueIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(bet_murderer);
    int betMurdererIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(bet_owner);
    int betOwnerIdx = manager.nodes.size() - 1;


    manager.nodes[rootIdx].next_nodes = {continueIdx};
    manager.nodes[continueIdx].next_nodes = {betMurdererIdx, betOwnerIdx};

}
