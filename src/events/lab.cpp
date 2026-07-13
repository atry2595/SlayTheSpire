#include "lab.h"

#include "utils/RNG.h"
#include "categories/potions.h"
#include "items/potions/potionfactory.h"
Lab::Lab(game_action& actions, ironclad* player)
{
    Q_UNUSED(actions);

    manager.unknown_ID = unknownID::lab;
    manager.unknown_name = tr("Lab");
    manager.isEvent = true;

    UnknownNode root;

    root.actions = [](){};

    root.canUse = [](){ return true; };

    root.title = "";

    root.description =
        tr("You find yourself in a room filled with racks of test tubes, beakers, flasks, forceps, pinch clamps, stirring rods, tongs, goggles, funnels, pipets, cylinders, condensers, and even a rare spiral tube of glass.\n\n"
           "Why do you know the names of all these tools? It doesn't matter, you take a look around.");

    UnknownNode search;

    search.title =tr("[Search] Find some Potions!");

    search.description =tr("You rummage through the laboratory and discover several useful potions.");

    search.actions = [player]()
    {
        std::vector<potionID> pool = common_potions;

        pool.insert(pool.end(),uncommon_potions.begin(),uncommon_potions.end());

        pool.insert(pool.end(),rare_potions.begin(),rare_potions.end());

        RNG::instance().shuffle(pool);

        search.actions = [player]()
        {
            std::vector<potionID> pool = common_potions;

            pool.insert(pool.end(),uncommon_potions.begin(),uncommon_potions.end());

            pool.insert(pool.end(),rare_potions.begin(),rare_potions.end());

            RNG::instance().shuffle(pool);

            for (int i = 0; i < 3 && i < static_cast<int>(pool.size()); i++)
            {
                abstractPotion* potion =PotionFactory::createPotion(pool[i], player);

                if (potion)
                    player->potion_list_add(potion);
            }
        };
    };

    search.canUse = [](){ return true; };

    search.next_nodes = {-1};

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(search);
    int searchIdx = manager.nodes.size() - 1;

    manager.nodes[rootIdx].next_nodes =
        {
            searchIdx
        };
}