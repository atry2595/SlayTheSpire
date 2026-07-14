#include "bonfirespirits.h"
#include "cards/cardfactory.h"
#include "items/relics/relicfactory.h"

BonfireSpirits::BonfireSpirits(game_action& actions, ironclad* player) {
    manager.unknown_ID = unknownID::bonfire_spirits;
    manager.unknown_name = tr("Bonfire Spirits");
    manager.isEvent = true;

    UnknownNode root;
    root.actions = [](){};
    root.canUse = [](){ return true; };
    root.description = tr("You happen upon what looks like a group of purple fire spirits dancing around a large bonfire.\n\n"
                          "The spirits toss small bones and fragments into the fire, which brilliantly erupts each time.\n"
                          "As you approach, the spirits all turn to you, expectantly...");
    root.title = "";

    UnknownNode offer_node;
    offer_node.title = tr("[Offer] Receive a reward based on the rarity of the card you give.");
    offer_node.canUse = [](){ return true; };
    offer_node.actions = [player, &actions, &offer_node] () {

        std::vector<abstractCard*> deck = player->get_deck();
        if (deck.empty()) return;

        abstractCard* selected = ironclad::select_card(deck);
        if (!selected) return;

        player->deck_remove(selected);

        if (selected->get_card_type() == CardType::curse) {
            auto rlc = RelicFactory::createRelic(relicID::spirit_poop, player);
            player->add_relic(actions, rlc);
            offer_node.description = tr("However, the spirits aren't happy you offered a Curse.../nThe card fizzles a meek black smoke. You receive a... something in return.");
        }
        else if (selected->is_rare()) {
            player->set_max_hp(player->get_max_hp() + 10);
            healInfo inf;
            inf.value = player->get_max_hp() - player->get_hp();
            inf.owner = player;
            actions.heal(inf);

            offer_node.description = tr("The flames burst, nearly knocking you off your feet, as the fire doubles in strength./nThe spirits dance around you excitedly before merging into your form, filling you with warmth and strength./nYour Max HP increases by 10 and you are healed to full HP.");
        }
        else if (selected->get_card_id() == cardID::strike || selected->get_card_id() == cardID::defend){
            offer_node.description = tr("Nothing happens...\nThe spirits seem to be ignoring you now. Disappointing...");
        }
        else {
            healInfo inf;
            inf.value = 5;
            inf.owner = player;
            actions.heal(inf);

            offer_node.description = tr("The flames grow slightly brighter./nThe spirits continue dancing. You feel slightly warmer from their presence../nYou heal 5 HP.");

        }



    };
    offer_node.next_nodes = {-1};

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(offer_node);
    int offerIdx = manager.nodes.size() - 1;

    manager.nodes[rootIdx].next_nodes = {offerIdx};
}
