#include "book_of_stabbing.h"
#include "items/powers/powerfactory.h"

book_of_stabbing::book_of_stabbing(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


book_of_stabbing* book_of_stabbing::create(game_action& actions){

    QString name = tr("Book Of Stabbing");

    RNG& rng = RNG::instance();
    int hp = rng.randint(160, 164);

    book_of_stabbing* enemy = new book_of_stabbing(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Multi Stab");
    intnt1.type = intent_type::attack;
    intnt1.damage = 6;
    intnt1.repeat = 2;

    enemy_intent intnt2;
    intnt2.name = tr("Big Stab");
    intnt2.type = intent_type::attack;
    intnt2.damage = 21;


    enemy->intent_list[(int)book_of_stabbing_move::multi_stab] = intnt1;
    enemy->intent_list[(int)book_of_stabbing_move::big_stab] = intnt2;

    if (rng.chance(0.85)) enemy->current_move = (int)book_of_stabbing_move::multi_stab;
    else enemy->current_move = (int)book_of_stabbing_move::big_stab;

    abstractPower* p = PowerFactory::createPower(powerID::painful_stabs, enemy, 1);
    enemy->add_power(actions, p);

    return enemy;
}



void book_of_stabbing::choose_move() {
    RNG& rng = RNG::instance();
    int tmp = current_move;

    if (current_move == last_move && current_move == (int)book_of_stabbing_move::multi_stab) {
        current_move = (int)book_of_stabbing_move::big_stab;
    }
    else if (current_move == (int)book_of_stabbing_move::big_stab) {
        current_move = (int)book_of_stabbing_move::multi_stab;
    }
    else {
        if (rng.chance(0.85)) current_move = (int)book_of_stabbing_move::multi_stab;
        else current_move = (int)book_of_stabbing_move::big_stab;
    }

    last_move = tmp;
}



void book_of_stabbing::play_turn(playInfo& info){

    switch((book_of_stabbing_move)current_move){


    case (book_of_stabbing_move::multi_stab):{

        perform_attack(info);
        intent_list[current_move].repeat++;

        break;
    }


    case (book_of_stabbing_move::big_stab): {

        perform_attack(info);

        break;
    }

    }

    enemy_turn++;
    choose_move();
}

QString book_of_stabbing::get_story() {
    return (QObject::tr("The Book of Stabbing hovers in the Spire's heavy air, its pages turning with the relentless rhythm of an angry heartbeat.\nFrom its cursed lines, a blade is born, again and again, as if spelling out an endless legend punctuated only by blood."));
}
