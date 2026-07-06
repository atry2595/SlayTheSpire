#include "hexaghost.h"
#include "items/powers/powerfactory.h"
#include "entity/ironclad.h"
#include "cards/status/burn.h"

hexaghost::hexaghost(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


hexaghost* hexaghost::create(game_action& actions){

    QString name = tr("Hexaghost");

    RNG& rng = RNG::instance();
    int hp = 250;

    hexaghost* enemy = new hexaghost(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Activate");
    intnt1.type = intent_type::special;

    enemy_intent intnt2;
    intnt2.name = tr("Divider");
    intnt2.type = intent_type::attack;
    intnt2.damage = 0;
    intnt2.repeat = 6;


    enemy_intent intnt3;
    intnt3.name = tr("Sear");
    intnt3.type = intent_type::attack_debuff;
    intnt3.damage = 6;

    enemy_intent intnt4;
    intnt4.name = tr("Tackle");
    intnt4.type = intent_type::attack;
    intnt4.damage = 5;
    intnt4.repeat = 2;

    enemy_intent intnt5;
    intnt5.name = tr("Inflame");
    intnt5.type = intent_type::block_buff;

    enemy_intent intnt6;
    intnt6.name = tr("Inferno");
    intnt6.type = intent_type::attack_debuff;
    intnt6.damage = rng.randint(2, 3);
    intnt6.repeat = 6;

    enemy->intent_list[(int)hexaghost_move::activate] = intnt1;
    enemy->intent_list[(int)hexaghost_move::divider] = intnt2;
    enemy->intent_list[(int)hexaghost_move::sear] = intnt3;
    enemy->intent_list[(int)hexaghost_move::tackle] = intnt4;
    enemy->intent_list[(int)hexaghost_move::inflame] = intnt5;
    enemy->intent_list[(int)hexaghost_move::inferno] = intnt6;

    enemy->current_move = (int)hexaghost_move::activate;

    return enemy;
}



void hexaghost::choose_move() {
    if (enemy_turn == 0) current_move = (int)hexaghost_move::activate;
    else if (enemy_turn == 1) current_move = (int)hexaghost_move::divider;
    else if (enemy_turn % 7 == 2 || enemy_turn % 7 == 4 || enemy_turn % 7 == 0) current_move = (int)hexaghost_move::sear;
    else if (enemy_turn % 7 == 3 || enemy_turn % 7 == 6) current_move = (int)hexaghost_move::tackle;
    else if (enemy_turn % 7 == 5) current_move = (int)hexaghost_move::inflame;
    else if (enemy_turn % 7 == 1) current_move = (int)hexaghost_move::inferno;
}



void hexaghost::play_turn(playInfo& info){

    switch((hexaghost_move)current_move){


    case (hexaghost_move::activate):{

        break;
    }


    case (hexaghost_move::divider): {


        playInfo new_info(info.actions);
        new_info.attacker = info.attacker;

        for (auto item : info.target_list) {
            new_info.target_list = {item};
            intent_list[current_move].damage = (int) item->get_hp() / 12;

            perform_attack(new_info);
        }

        break;
    }

    case (hexaghost_move::sear): {

        int card_count = 1;

        perform_attack(info);

        for (auto item : info.target_list) {
            ironclad* player = dynamic_cast<ironclad*>(item);
            if (!player) continue;
            for (int i = 0; i<card_count; i++) {
                burn* nc = new burn();
                if (upgrade_burn) nc->curse_upgrade();
                player->discard_pile_add(nc, true);
            }
        }

        break;
    }

    case (hexaghost_move::tackle): {

        perform_attack(info);
        break;
    }

    case (hexaghost_move::inflame): {

        int effect_number = 2;
        int block_number = 12;

        perform_block(info, block_number);

        abstractPower* np1 = PowerFactory::createPower(powerID::strength, this, effect_number);
        this->add_power(info.actions, np1);

        break;
    }

    case (hexaghost_move::inferno): {

        int card_count = 3;

        perform_attack(info);

        for (auto item : info.target_list) {
            ironclad* player = dynamic_cast<ironclad*>(item);
            if (!player) continue;
            for (int i = 0; i<card_count; i++) {
                burn* nc = new burn();
                nc->curse_upgrade();
                player->discard_pile_add(nc, true);
            }
        }
        upgrade_burn = true;
        break;
    }

    }

    enemy_turn++;
    choose_move();
}