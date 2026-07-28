#include "shininglight.h"
#include "assetsManager/soundmanager.h"

#include "utils/RNG.h"

ShiningLight::ShiningLight(game_action& actions, ironclad* player)
{
    manager.unknown_ID = unknownID::shining_light;
    manager.unknown_name = tr("Shining Light");
    manager.isEvent = true;

    UnknownNode root;
    root.actions = [](){};
    root.canUse = [](){ return true; };

    root.title = "";

    root.description =tr(
        "You find a shimmering mass of light encompassing the center of the room.\n\n"
        "Its warm glow and enchanting patterns invite you in.");

    UnknownNode enter;
    int dmg = (int) player->get_max_hp() / 5;
    enter.title =tr(
                      "[Enter] Upgrade 2 random cards. Lose %1 HP.").arg(dmg);

    enter.description =tr(
        "As you walk through the light, you notice that the light is absorbed into you.\n"
        "It's scorching hot! However, the pain quickly recedes.\n\n"
        "You feel invigorated, as though you received a well deserved slap.");

    enter.actions = [player, eve = actions.get_event(), dmg]()
    {
        soundManager::instance().playSoundEffect(SoundEffect::smith);
        game_action actions(eve);
        damageInfo inf;
        inf.damage = dmg;
        inf.attacker = nullptr;
        inf.block_active = false;
        inf.target = player;

        actions.apply_damage(inf);

        std::vector<abstractCard*> cards;

        for(auto card : player->get_deck())
        {
            if(!card->get_upgraded() &&card->get_card_type() != CardType::curse &&card->get_card_type() != CardType::status)
            {
                cards.push_back(card);
            }
        }

        if(cards.empty())
            return;

        RNG::instance().shuffle(cards);

        cards[0]->base_upgrade();

        if(cards.size() >= 2)
            cards[1]->base_upgrade();
    };

    enter.canUse = [](){ return true; };
    enter.next_nodes = {-1};

    UnknownNode leave;


    manager.nodes.push_back(root);
    int rootIdx = manager.nodes.size() - 1;

    manager.nodes.push_back(enter);
    int enterIdx = manager.nodes.size() - 1;


    manager.nodes[rootIdx].next_nodes =
        {
            enterIdx,
            -1
        };
}