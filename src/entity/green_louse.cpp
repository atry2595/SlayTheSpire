#include "green_louse.h"
#include "items/powers/powerfactory.h"

green_louse::green_louse(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


green_louse* green_louse::create(game_action& actions){

    QString name = tr("Green Louse");

    RNG& rng = RNG::instance();
    int hp = rng.randint(11, 17);

    green_louse* enemy = new green_louse(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Bite");
    intnt1.type = intent_type::attack;
    intnt1.damage = rng.randint(5, 7);

    enemy_intent intnt2;
    intnt2.name = tr("Spit Web");
    intnt2.type = intent_type::debuff;


    enemy->intent_list[(int)green_louse_move::bite] = intnt1;
    enemy->intent_list[(int)green_louse_move::spit_web] = intnt2;

    if (rng.chance(0.25)) enemy->current_move = (int)green_louse_move::spit_web;
    else enemy->current_move = (int)green_louse_move::bite;

    abstractPower* p = PowerFactory::createPower(powerID::curl_up, enemy, 1);
    enemy->add_power(actions, p);

    return enemy;
}



void green_louse::choose_move() {
    RNG& rng = RNG::instance();

    int tmp = current_move;

    if (current_move == last_move && current_move == (int)green_louse_move::spit_web) current_move = (int)green_louse_move::bite;
    else if (current_move == last_move && current_move == (int)green_louse_move::bite) current_move = (int)green_louse_move::spit_web;
    else if (rng.chance(0.25)) current_move = (int)green_louse_move::spit_web;
    else current_move = (int)green_louse_move::bite;

    last_move = tmp;
}



void green_louse::play_turn(playInfo& info){

    switch((green_louse_move)current_move){


    case (green_louse_move::bite):{

        perform_attack(info);

        break;
    }


    case (green_louse_move::spit_web): {

        int effect_number = 2;

        for (auto item : info.target_list){
            abstractPower* np = PowerFactory::createPower(powerID::weak, item, effect_number);
            item->add_power(info.actions, np);
        }

        break;
    }

    }

    enemy_turn++;
    choose_move();
}

QString green_louse::get_story() {
    return (QObject::tr("The Green Louse puffs a cloud of weakening spores and lurks within its own sickly mist.\nIn that sickening veil, it dreams of becoming a world-eating plague, never knowing it will never crawl beyond a single stone's shadow in the Spire."));
}
