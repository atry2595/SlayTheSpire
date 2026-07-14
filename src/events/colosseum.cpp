#include "colosseum.h"

#include "cards/cardfactory.h"
#include "items/relics/relicfactory.h"

Colosseum::Colosseum(game_action& actions, ironclad* player) {
    // //atry: مقدار unknownID::colosseum را به enumهای مربوطه اضافه کن.
    manager.unknown_ID = unknownID::colosseum;
    manager.unknown_name = tr("The Colosseum");
    manager.isEvent = true;

    UnknownNode root;
    root.title = "";
    root.description = tr("Thwack!!!\n"
                          "..\n"
                          "......\n"
                          "...\n"
                          "You were knocked unconscious...");
    root.canUse = []() { return true; };
    root.actions = []() {};

    UnknownNode wake_up_node;
    wake_up_node.title = tr("[Continue]");
    wake_up_node.description = tr("Groggy and with a throbbing head, you awaken to find yourself thrown in the center of a massive stadium with an overflowing audience of Slavers, Cultists, and other denizens of the City!\n\n"
                                  "An armored giant with a golden crown bellows at you from atop,\n"
                                  "\"WE NOW BEGIN THE 4200TH COMBAT!!!!\"\n"
                                  "A gate on the opposite side opens...");
    wake_up_node.canUse = []() { return true; };
    wake_up_node.actions = []() {};

    UnknownNode fight_one_node;
    fight_one_node.title = tr("[Fight] Enter combat with Blue Slaver and Red Slaver.");
    fight_one_node.description = "";
    fight_one_node.canUse = []() { return true; };

    UnknownNode choice_node;
    choice_node.title = tr("[Continue]");
    choice_node.description = tr("\"WELL DONE, WEAKLING!\"\n"
                                 "The giant mock claps whilst he riles up the crowd with exaggerated gestures.\n"
                                 "Gold and confetti shower you!\n"
                                 "\"TIME FOR THE REAL CHALLENGE!!\"\n\n"
                                 "The last battle left a small hole in the Colosseum's wall, you can easily escape through there while everyone is distracted.\n"
                                 "Do you stay and fight?");
    choice_node.canUse = []() { return true; };
    choice_node.actions = []() {};

    UnknownNode cowardice_node;
    cowardice_node.title = tr("[COWARDICE] Escape.");
    cowardice_node.description = "";
    cowardice_node.canUse = []() { return true; };
    cowardice_node.actions = []() {};
    cowardice_node.next_nodes = {-1};

    UnknownNode victory_node;
    victory_node.title = tr("[VICTORY] A powerful fight with many rewards.");
    victory_node.description = "";
    victory_node.canUse = []() { return true; };

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(wake_up_node);
    int wakeUpIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(fight_one_node);
    int fightOneIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(choice_node);
    int choiceIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(cowardice_node);
    int cowardiceIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(victory_node);
    int victoryIdx = manager.nodes.size() - 1;


    manager.nodes[rootIdx].next_nodes = {wakeUpIdx};
    manager.nodes[wakeUpIdx].next_nodes = {fightOneIdx};
    manager.nodes[fightOneIdx].next_nodes = {choiceIdx};
    manager.nodes[choiceIdx].next_nodes = {cowardiceIdx, victoryIdx};
    manager.nodes[victoryIdx].next_nodes = {-1};


    //atry: نحوه شروع مبارزه عادی و فراخوانی دشمنان (Blue Slaver و Red Slaver) را بر اساس سیستم مبارزه پروژه تنظیم کن.
    manager.nodes[fightOneIdx].actions = [&actions, player]() {
        // ??
    };


    // //atry: شروع مبارزه الیت با Gremlin Nob و Taskmaster و ست کردن جوایز آن شامل ۱۰۰ سکه طلا، یک رلیک Rare و یک رلیک Uncommon.
    manager.nodes[victoryIdx].actions = [&actions, player]() {
        // شروع مبارزه الیت دوم
        // actions.start_combat({enemyID::taskmaster, enemyID::gremlin_nob}, combatType::elite);

        // اهدای پاداش‌ها (می‌تواند مستقیم به موجودی بازیکن اضافه شود یا از طریق سیستم پاداش مبارزه (combatRewards) هندل شود):
        player->set_gold(player->get_gold() + 100);

        //atry: سیستم گرفتن رلیک تصادفی بر اساس Rarity را فراخوانی کنید.
        //??
    };
}
