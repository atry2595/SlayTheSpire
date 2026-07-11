#include "ominousforge.h"
#include "cards/cardfactory.h"
#include "items/relics/relicfactory.h"

OminousForge::OminousForge(game_action& actions, ironclad* player) {

    manager.unknown_ID = unknownID::ominous_forge;
    manager.unknown_name = tr("Ominous Forge");
    manager.isEvent = true;


    UnknownNode root;
    root.actions = [](){};
    root.canUse = [](){ return true; };
    root.description = tr("You duck inside a small hut. Inside you find what appears to be a forge. The smithing tools are covered with dust, yet a fire roars inside the furnace. You feel on edge...");
    root.title = "";

    //---------------------------------------------------

    UnknownNode forge_node;
    forge_node.title = tr("[Forge] Upgrade a card in your deck.");
    forge_node.description = tr("You decide to put the forge to use and...\nCLANG CLAAANG CLANG!\n...improve your arsenal!");
    forge_node.actions = [player] () {

        std::vector<abstractCard*> unupgraded_card;
        for (auto item : player->get_deck()){
            if (item->get_upgraded() == false && item->get_card_type() != CardType::curse) {
                unupgraded_card.push_back(item);
            }
        }

        abstractCard* selected_card = ironclad::select_card(unupgraded_card);
        selected_card->base_upgrade();
    };
    forge_node.canUse = [](){ return true; };
    forge_node.next_nodes = {-1};

    //---------------------------------------------------

    UnknownNode rummage_node;
    rummage_node.title = tr("[Rummage] Obtain a special relic. Become Cursed - Pain.");
    rummage_node.description = tr("You decide to see if you can find anything of use. After uncovering tarps, looking through boxes, and checking nooks and crannies, you find a dust covered relic!\n\nTaking the relic, you can't shake a sudden feeling of sharp pain as you exit the hut. Maybe you disturbed some sort of spirit?");
    rummage_node.actions = [player, &actions] () {

        abstractRelic* relic = RelicFactory::createRelic(relicID::warped_tongs, player);
        player->add_relic(actions, relic);

        abstractCard* card = CardFactory::createCard(cardID::pain);
        player->deck_add(card);

    };
    rummage_node.canUse = [](){ return true; };
    rummage_node.next_nodes = {-1};

    //---------------------------------------------------

    manager.nodes.push_back(root);

    manager.nodes.push_back(forge_node);
    int forgeIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(rummage_node);
    int rummageIdx = manager.nodes.size() - 1;

    manager.nodes[0].next_nodes = {forgeIdx, rummageIdx, -1};
}
