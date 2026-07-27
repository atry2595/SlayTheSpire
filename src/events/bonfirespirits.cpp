// #include "bonfirespirits.h"
// #include "cards/cardfactory.h"
// #include "items/relics/relicfactory.h"

// BonfireSpirits::BonfireSpirits(game_action& actions, ironclad* player) {
//     manager.unknown_ID = unknownID::bonfire_spirits;
//     manager.unknown_name = tr("Bonfire Spirits");
//     manager.isEvent = true;

//     UnknownNode root;
//     root.actions = [](){};
//     root.canUse = [](){ return true; };
//     root.description = tr("You happen upon what looks like a group of purple fire spirits dancing around a large bonfire.\n\n"
//                           "The spirits toss small bones and fragments into the fire, which brilliantly erupts each time.\n"
//                           "As you approach, the spirits all turn to you, expectantly...");
//     root.title = "";

    UnknownNode offer_node;
    offer_node.title = tr("[Offer] Receive  a  reward   based   on\n"
                          "        the rarity of the card you give.");
    offer_node.canUse = [](){ return true; };
    offer_node.description = tr("The flames come alive with your offering, and the spirits, amidst the smoke and dance of fire, give a mysterious answer.");
    offer_node.actions = [player, eve = actions.get_event(), &offer_node] () {

//         std::vector<abstractCard*> deck = player->get_deck();
//         if (deck.empty()) return;



        std::vector<abstractCard*> sc;
        for (auto item : deck) {
            if (item->can_remove_from_deck()) sc.push_back(item);
        }

        emit eve->selectCard(sc);
        auto conn = std::make_shared<QMetaObject::Connection>();
        *conn = connect(eve, &combatEvent::cardSelected, eve, [=](abstractCard* selected){

            if (selected){
                game_action actions(eve);

                if (selected->get_card_type() == CardType::curse) {
                    auto rlc = RelicFactory::createRelic(relicID::spirit_poop, player);
                    player->add_relic(actions, rlc);
                }

                else if (selected->is_rare()) {
                    player->set_max_hp(player->get_max_hp() + 10);
                    healInfo inf;
                    inf.value = player->get_max_hp() - player->get_hp();
                    inf.owner = player;
                    actions.heal(inf);

                }

                else if (selected->get_card_id() == cardID::strike || selected->get_card_id() == cardID::defend) {}

                else {
                    healInfo inf;
                    inf.value = 5;
                    inf.owner = player;
                    actions.heal(inf);

                }

                player->deck_remove(selected);
                emit eve->barUpdate();
            }

            disconnect(*conn);

        });




//     };
//     offer_node.next_nodes = {-1};

//     manager.nodes.push_back(root);
//     int rootIdx = manager.nodes.size() - 1;

//     manager.nodes.push_back(offer_node);
//     int offerIdx = manager.nodes.size() - 1;

//     manager.nodes[rootIdx].next_nodes = {offerIdx};
// }
