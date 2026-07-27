#include "red_slaver.h"
#include "items/powers/powerfactory.h"

red_slaver::red_slaver(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


red_slaver* red_slaver::create(game_action& actions){

    QString name = tr("Red Slaver");

    RNG& rng = RNG::instance();
    int hp = rng.randint(46, 50);

    red_slaver* enemy = new red_slaver(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Stab");
    intnt1.type = intent_type::attack;
    intnt1.damage = 13;

    enemy_intent intnt2;
    intnt2.name = tr("Scrape");
    intnt2.type = intent_type::attack_debuff;
    intnt2.damage = 8;

    enemy_intent intnt3;
    intnt3.name = tr("Entangle");
    intnt3.type = intent_type::debuff;


    enemy->intent_list[(int)red_slaver_move::stab] = intnt1;
    enemy->intent_list[(int)red_slaver_move::scrape] = intnt2;
    enemy->intent_list[(int)red_slaver_move::entangle] = intnt3;

    enemy->current_move = (int)red_slaver_move::stab;

    return enemy;
}



void red_slaver::choose_move() {
    RNG& rng = RNG::instance();

    int tmp = current_move;

    if (entangle_used == false) {

        if (rng.chance(0.25)) {
            current_move = (int)red_slaver_move::entangle;
        }
        else if (current_move == last_move && current_move == (int)red_slaver_move::scrape) {
            current_move = (int)red_slaver_move::stab;
        }
        else if (current_move == (int)red_slaver_move::scrape) {
            current_move = (int)red_slaver_move::scrape;
        }
        else {
            current_move = (int)red_slaver_move::scrape;
        }
    }

    else {
        if (current_move == last_move && current_move == (int)red_slaver_move::scrape) {
            current_move = (int)red_slaver_move::stab;
        }
        else if (current_move == last_move && current_move == (int)red_slaver_move::stab) {
            current_move = (int)red_slaver_move::scrape;
        }
        else {
            if (rng.chance(0.55)) current_move = (int)red_slaver_move::stab;
            else current_move = (int)red_slaver_move::scrape;
        }
    }

    last_move = tmp;
}



void red_slaver::play_turn(playInfo& info){

    switch((red_slaver_move)current_move){


    case (red_slaver_move::stab):{

        perform_attack(info);

        break;
    }


    case (red_slaver_move::scrape): {

        int effect_number = 1;

        perform_attack(info);

        for (auto item : info.target_list) {
            abstractPower* np = PowerFactory::createPower(powerID::vulnerable, item, effect_number);
            item->add_power(info.actions, np);
        }

        break;
    }


    case (red_slaver_move::entangle):{

        int effect_number = 1;

        for (auto item : info.target_list) {
            abstractPower* np = PowerFactory::createPower(powerID::entangled, item, effect_number);
            item->add_power(info.actions, np);
        }
        entangle_used = true;

        break;

    }


    }

    enemy_turn++;
    choose_move();
}

QString red_slaver::get_story() {
    return (QObject::tr("The Red Slaver keeps his brand hot and paces the empty corridor with brutal pride, chains glowing.\nBut his searing links bind nothing but the Spire's cold air, and the embers illuminate only his captiveless solitude."));
}
