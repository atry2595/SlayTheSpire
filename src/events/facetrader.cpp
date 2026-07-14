#include "facetrader.h"

#include "items/relics/relicfactory.h"
#include "utils/RNG.h"
FaceTrader::FaceTrader(game_action& actions, ironclad* player)
{
    manager.unknown_ID = unknownID::face_trader;
    manager.unknown_name = tr("Face Trader");
    manager.isEvent = true;

    UnknownNode root;
    root.title = "";
    root.description = tr(
        "You walk by an eerie statue holding several masks...\n"
        "Something behind you softly whispers,\n"
        "\"Stop.\""
        );

    root.actions = [](){};
    root.canUse = [](){ return true; };

    UnknownNode continue_node;
    continue_node.title = tr("[Continue]");

    continue_node.description = tr(
        "You swerve around to face the statue which is now facing you!\n\n"
        "On closer inspection, it's not a statue but a statuesque, gaunt man. Is he even breathing?\n\n"
        "\"Face. Let me touch? Maybe trade?\""
        );

    continue_node.actions = [](){};
    continue_node.canUse = [](){ return true; };


    UnknownNode touch_node;
    int dmg = (int) player->get_max_hp() / 10;
    touch_node.title = tr("[Touch] Lose %1 HP, gain 75 (50)Ascension.png 15 Gold.").arg(dmg);

    touch_node.description = tr(
        "\"Compensation? Compensation.\"\n\n"
        "Mechanically, he cranes out a neat stack of gold and places it in your pouch.\n\n"
        "\"What a nice face. Nice face.\"\n"
        "While he touches your face, you begin to feel your life drain out of it!\n"
        "During this, his mask falls off and shatters. Screaming, he quickly covers his face with all six arms dropping even more masks! Amidst all the screaming and shattering, you escape.\n\n"
        "His face was completely blank."
        );


    touch_node.actions =[player, &actions, dmg]()
    {

        damageInfo inf;
        inf.damage = dmg;
        inf.block_active = false;
        inf.target = player;
        inf.attacker = nullptr;

        actions.apply_damage(inf);

        player->earn_coin(75);
    };

    touch_node.canUse = [](){ return true; };
    touch_node.next_nodes = {-1};


    UnknownNode trade_node;

    trade_node.title = tr("[Trade] 50%: Good Face. 50%: Bad Face.");

    trade_node.description = tr(
        "\"For me? FOR ME? Oh yes.. Yes. Yes.. mmm...\"\n\n"
        "You see one of his arms flicker, and your face is in its hand! Your face has been swapped.\n\n"
        "\"Nice face. Nice face.\""
        );

    trade_node.actions =[player, &actions]()
    {
        relicID relic;

        int roll = RNG::instance().randint(0, 2);

        switch (roll)
        {
        case 0:
            relic = relicID::helmet_of_the_cleric;
            break;

        case 1:
            relic = relicID::gremlin_visage;
            break;

        default:
            relic = relicID::cultist_headpiece;
            break;
        }

        abstractRelic* reward =RelicFactory::createRelic(relic, player);

        player->add_relic(actions, reward);
    };

    trade_node.canUse = [](){ return true; };
    trade_node.next_nodes = {-1};


    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(continue_node);
    int continueIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(touch_node);
    int touchIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(trade_node);
    int tradeIdx = manager.nodes.size() - 1;


    manager.nodes[rootIdx].next_nodes =
        {
            continueIdx
        };

    manager.nodes[continueIdx].next_nodes =
        {
            touchIdx,
            tradeIdx,
            -1
        };
}