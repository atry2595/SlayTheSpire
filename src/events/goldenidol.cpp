#include "goldenidol.h"
#include "cards/cardfactory.h"
#include "items/relics/relicfactory.h"

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
    take_node.title = tr("[Take] Obtain Golden Idol. Trigger a trap.");
    take_node.description = tr(
        "As you grab the Idol and stow it away, a giant boulder smashes through the ceiling into the ground next to you.\n\n"
        "You realize that the floor is slanted downwards as the boulder starts to roll towards you."
        );

    take_node.actions = [player, &actions]()
    {
        player->add_relic(actions, RelicFactory::createRelic(relicID::golden_idol, player));
    };

    take_node.canUse = [](){ return true; };


    UnknownNode outrun_node;
    outrun_node.title = tr("[Outrun] Become Cursed - Injury.");
    outrun_node.description = tr(
        "RUUUUUUUUUUN!\n\n"
        "You barely leap into a side passageway as the boulder rushes by.\n"
        "Unfortunately it feels like you sprained something however."
        );

    outrun_node.actions = [player]()
    {
        player->deck_add(CardFactory::createCard(cardID::injury));
    };

    outrun_node.canUse = [](){ return true; };
    outrun_node.next_nodes = {-1};

    UnknownNode smash_node;
    int dmg = (int) player->get_max_hp() / 4;
    smash_node.title = tr("[Smash] Take %1 Damage.").arg(dmg);
    smash_node.description = tr(
        "You throw yourself at the boulder with everything you have. When the dust clears, you can make a safe way out."
        );

    smash_node.actions = [player, &actions, dmg]()
    {
        damageInfo inf;
        inf.damage = dmg;
        inf.attacker = nullptr;
        inf.block_active = false;
        inf.target = player;

        actions.apply_damage(inf);
    };

    smash_node.canUse = [](){ return true; };
    smash_node.next_nodes = {-1};

    UnknownNode hide_node;
    int lmh = (int) player->get_max_hp() * 8 / 100;
    hide_node.title = tr("[Hide] Lose %1 Max HP.").arg(lmh);
    hide_node.description = tr(
        "SQUISH!\n"
        "The boulder flattens you a little as it passes by, but otherwise you can get out of here."
        );

    hide_node.actions = [player, lmh]()
    {
        player->set_max_hp(player->get_max_hp() - lmh);
    };

    hide_node.canUse = [](){ return true; };
    hide_node.next_nodes = {-1};


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


    manager.nodes[rootIdx].next_nodes =
        {
            takeIdx,
            -1
        };

    manager.nodes[takeIdx].next_nodes =
        {
            outrunIdx,
            smashIdx,
            hideIdx
        };
}