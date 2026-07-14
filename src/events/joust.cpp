#include "joust.h"
#include "utils/RNG.h"

Joust::Joust(game_action& actions, ironclad* player) {
    // //atry: مقدار unknownID::joust را در صورت نیاز به لیست enumهای پروژه اضافه کن.
    manager.unknown_ID = unknownID::joust;
    manager.unknown_name = tr("The Joust");
    manager.isEvent = true;

    UnknownNode root;
    root.title = "";
    root.description = tr("As you make your way through the large buildings you come across a long narrow bridge and spot knights on either side, facing one another.\n"
                          "You approach...\n"
                          "\"HALT!\"\n\n"
                          "A knight forcefully gestures you to stop with its giant lance.");
    root.canUse = []() { return true; };
    root.actions = []() {};

    UnknownNode continue_node;
    continue_node.title = tr("[Continue]");
    continue_node.description = tr("\"Today is the day I must settle the score with the murderer of my beloved pet, Noodles. Until then, you may not pass.\n\n"
                                   "Fellow witness, why don't you bet on who you think will emerge victorious?\"");

    continue_node.canUse = []() { return true; };
    continue_node.actions = []() {};

    UnknownNode win_node;
    win_node.title = tr("[Continue]");
    win_node.description = tr("You win the bet. Unsure what to think, you grab your winnings and leave.");
    win_node.canUse = []() { return true; };
    win_node.actions = []() {};
    win_node.next_nodes = {-1};

    UnknownNode lose_node;
    lose_node.title = tr("[Continue]");
    lose_node.description = tr("You lost the bet, but at least you weren't gouged by a lance.");
    lose_node.canUse = []() { return true; };
    lose_node.actions = []() {};
    lose_node.next_nodes = {-1};

    UnknownNode bet_murderer;
    bet_murderer.title = tr("[Murderer] Bet 50 Gold - 70%: win 100 Gold.");
    bet_murderer.canUse = [player]() {
        return player->get_gold() >= 50;
    };


    UnknownNode bet_owner;
    bet_owner.title = tr("[Owner] Bet 50 Gold - 30%: win 250 Gold.");
    bet_owner.canUse = [player]() {
        return player->get_gold() >= 50;
    };

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(continue_node);
    int continueIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(bet_murderer);
    int betMurdererIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(bet_owner);
    int betOwnerIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(win_node);
    int winIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(lose_node);
    int loseIdx = manager.nodes.size() - 1;

    manager.nodes[rootIdx].next_nodes = {continueIdx};
    manager.nodes[continueIdx].next_nodes = {betMurdererIdx, betOwnerIdx};

    manager.nodes[betMurdererIdx].actions = [player, &manager, winIdx, loseIdx]() {
        player->set_gold(player->get_gold() - 50);

        bool win = RNG::instance().chance(0.7);

        if (win) {
            // //atry: در صورت پیاده‌سازی رلیک Ectoplasm، داشتن آن را بررسی کن تا طلا اضافه نشود.
            bool hasEctoplasm = player->has_relic(relicID::ectoplasm);
            if (!hasEctoplasm) {
                player->set_gold(player->get_gold() + 100);
            }
            manager.nodes[betMurdererIdx].next_nodes = {winIdx};
        } else {
            manager.nodes[betMurdererIdx].next_nodes = {loseIdx};
        }

        manager.nodes[betMurdererIdx].description = tr("\"I can't believe you're betting against Noodles!\"\n\n"
                                                       "Furious, he clamps down his helmet and rushes towards his nemesis.\n\n"
                                                       "* CRASH!!! * * KLAAAANG! *\n* POW! *");
    };

    manager.nodes[betOwnerIdx].actions = [player, &manager, winIdx, loseIdx]() {
        player->set_gold(player->get_gold() - 50);

        bool win = RNG::instance().chance(0.3);

        if (win) {
            // //atry: در صورت پیاده‌سازی رلیک Ectoplasm، داشتن آن را بررسی کن تا طلا اضافه نشود.
            bool hasEctoplasm = player->has_relic(relicID::ectoplasm);
            if (!hasEctoplasm) {
                player->set_gold(player->get_gold() + 250);
            }
            manager.nodes[betOwnerIdx].next_nodes = {winIdx};
        } else {
            manager.nodes[betOwnerIdx].next_nodes = {loseIdx};
        }

        manager.nodes[betOwnerIdx].description = tr("\"Give me strength, Noodles!\"\n\n"
                                                    "Clamping down his helmet, the knight charges forward.\n\n"
                                                    "* CRASH!!! * * KLAAAANG! *\n* POW! *");
    };
}
