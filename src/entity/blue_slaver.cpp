#include "blue_slaver.h"
#include "items/powers/powerfactory.h"

blue_slaver::blue_slaver(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


blue_slaver* blue_slaver::create(game_action& actions){

    QString name = tr("Blue Slaver");

    RNG& rng = RNG::instance();
    int hp = rng.randint(46, 50);

    blue_slaver* enemy = new blue_slaver(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Stab");
    intnt1.type = intent_type::attack;
    intnt1.damage = 12;

    enemy_intent intnt2;
    intnt2.name = tr("Rake");
    intnt2.type = intent_type::attack_debuff;
    intnt2.damage = 7;


    enemy->intent_list[(int)blue_slaver_move::stab] = intnt1;
    enemy->intent_list[(int)blue_slaver_move::rake] = intnt2;

    if (rng.chance(0.6)) enemy->current_move = (int)blue_slaver_move::stab;
    else enemy->current_move = (int)blue_slaver_move::rake;

    return enemy;
}



void blue_slaver::choose_move() {
    RNG& rng = RNG::instance();

    int tmp = current_move;

    if (current_move == last_move && current_move == (int)blue_slaver_move::stab) current_move = (int)blue_slaver_move::rake;
    else if (current_move == last_move && current_move == (int)blue_slaver_move::rake) current_move = (int)blue_slaver_move::stab;
    else if (rng.chance(0.6)) current_move = (int)blue_slaver_move::stab;
    else current_move = (int)blue_slaver_move::rake;

    last_move = tmp;
}



void blue_slaver::play_turn(playInfo& info){

    switch((blue_slaver_move)current_move){


    case (blue_slaver_move::stab):{

        perform_attack(info);

        break;
    }


    case (blue_slaver_move::rake): {

        int effect_number = 1;

        perform_attack(info);

        for (auto item : info.target_list) {
            abstractPower* np = PowerFactory::createPower(powerID::weak, item, effect_number);
            item->add_power(info.actions, np);
        }

        break;
    }


    }

    enemy_turn++;
    choose_move();
}

QString blue_slaver::get_story() {
    return (QObject::tr("The Blue Slaver cracks his whip against the Spire's cold stone, staring down a path that has seen no captives for years.\nHe never realizes that he, too, is a prisoner of this endless corridor, bound by a duty his masters abandoned centuries ago."));
}
