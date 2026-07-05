#include "red_louse.h"
#include "items/powers/powerfactory.h"

red_louse::red_louse(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


red_louse* red_louse::create(game_action& actions){

    QString name = tr("Red Louse");

    RNG& rng = RNG::instance();
    int hp = rng.randint(10, 15);

    red_louse* enemy = new red_louse(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Bite");
    intnt1.type = intent_type::attack;
    intnt1.damage = rng.randint(5, 7);

    enemy_intent intnt2;
    intnt2.name = tr("Grow");
    intnt2.type = intent_type::buff;


    enemy->intent_list[(int)red_louse_move::bite] = intnt1;
    enemy->intent_list[(int)red_louse_move::grow] = intnt2;

    if (rng.chance(0.25)) enemy->current_move = (int)red_louse_move::grow;
    else enemy->current_move = (int)red_louse_move::bite;

    abstractPower* p = PowerFactory::createPower(powerID::curl_up, enemy, 1);
    enemy->add_power(actions, p);

    return enemy;
}



void red_louse::choose_move() {
    RNG& rng = RNG::instance();

    if (rng.chance(0.25)) current_move = (int)red_louse_move::grow;
    else current_move = (int)red_louse_move::bite;
}



void red_louse::play_turn(playInfo& info){

    switch((red_louse_move)current_move){


    case (red_louse_move::bite):{

        perform_attack(info);

        break;
    }


    case (red_louse_move::grow): {

        int effect_number = 3;

        abstractPower* np = PowerFactory::createPower(powerID::strength, info.attacker, effect_number);
        info.attacker->add_power(info.actions, np);

        break;
    }

    }

    enemy_turn++;
    choose_move();
}