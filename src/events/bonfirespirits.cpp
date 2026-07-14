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
    offer_node.title = tr("[Offer] Offer a card in your deck to remove. Receive a reward based on the rarity of the card you give.");
    offer_node.canUse = [](){ return true; };
    offer_node.actions = [player, &actions, &offer_node] () {
        std::vector<abstractCard*> deck = player->get_deck();
        if (deck.empty()) return;

        abstractCard* selected = ironclad::select_card(deck);
        if (!selected) return;

        player->deck_remove(selected);

        CardType type = selected->get_card_type();
        CardRarity rarity = selected->get_rarity();

        if (type == CardType::curse) {
            offer_node.description = tr("You toss an offering into the bonfire.\n\n"
                                        "However, the spirits aren't happy you offered a Curse...\n"
                                        "The card fizzles a meek black smoke. You receive a... something in return.\n"
                                        "(Obtained Spirit Poop)");

            //atry: اگر شناسه relicID::spirit_poop تعریف نشده، آن را تعریف و پیاده‌سازی کن.
            abstractRelic* poop = RelicFactory::createRelic(relicID::spirit_poop, player);
            player->add_relic(actions, poop);
        }
        else if (rarity == CardRarity::basic) {
            offer_node.description = tr("You toss an offering into the bonfire.\n\n"
                                        "Nothing happens...\n"
                                        "The spirits seem to be ignoring you now. Disappointing...");
        }
        else if (rarity == CardRarity::common) {
            offer_node.description = tr("You toss an offering into the bonfire.\n\n"
                                        "The flames grow slightly brighter.\n"
                                        "The spirits continue dancing. You feel slightly warmer from their presence..\n"
                                        "You heal 5 HP.");

            player->set_hp(std::min(player->get_max_hp(), player->get_hp() + 5));
        }
        else if (rarity == CardRarity::uncommon) {
            offer_node.description = tr("You toss an offering into the bonfire.\n\n"
                                        "The flames erupt, growing significantly stronger!\n"
                                        "The spirits dance around you excitedly, filling you with a sense of warmth.\n"
                                        "You are healed to full HP.");

            player->set_hp(player->get_max_hp());
        }
        else if (rarity == CardRarity::rare) {
            offer_node.description = tr("You toss an offering into the bonfire.\n\n"
                                        "The flames burst, nearly knocking you off your feet, as the fire doubles in strength.\n"
                                        "The spirits dance around you excitedly before merging into your form, filling you with warmth and strength.\n"
                                        "Your Max HP increases by 10 and you are healed to full HP.");

            player->set_max_hp(player->get_max_hp() + 10);
            player->set_hp(player->get_max_hp());
        }
    };
    offer_node.next_nodes = {-1};

    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(offer_node);
    int offerIdx = manager.nodes.size() - 1;

    manager.nodes[rootIdx].next_nodes = {offerIdx};
}
