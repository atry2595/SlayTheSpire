#include "jaw_worm.h"
#include "items/powers/powerfactory.h"

jaw_worm::jaw_worm(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


jaw_worm* jaw_worm::create(game_action& actions){

    QString name = tr("Jaw Worm");

    RNG& rng = RNG::instance();
    int hp = rng.randint(40, 44);

    jaw_worm* enemy = new jaw_worm(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Chomp");
    intnt1.type = intent_type::attack;
    intnt1.damage = 11;

    enemy_intent intnt2;
    intnt2.name = tr("Bellow");
    intnt2.type = intent_type::block_buff;


    enemy_intent intnt3;
    intnt3.name = tr("Thrash");
    intnt3.type = intent_type::attack_block;
    intnt3.damage = 7;

    enemy->intent_list[(int)jaw_worm_move::chomp] = intnt1;
    enemy->intent_list[(int)jaw_worm_move::bellow] = intnt2;
    enemy->intent_list[(int)jaw_worm_move::thrash] = intnt3;

    enemy->current_move = (int)jaw_worm_move::chomp;

    return enemy;
}



void jaw_worm::choose_move() {
    RNG& rng = RNG::instance();

    switch((jaw_worm_move)current_move){

    case (jaw_worm_move::chomp):{
        if (rng.chance(0.59)) current_move = (int)jaw_worm_move::bellow;
        else current_move = (int)jaw_worm_move::thrash;
        break;
    }

    case (jaw_worm_move::bellow):{
        if (rng.chance(0.56)) current_move = (int)jaw_worm_move::thrash;
        else current_move = (int)jaw_worm_move::chomp;
        break;
    }

    case (jaw_worm_move::thrash):{
        double chance = rng.random();
        if (chance <= 0.493) current_move = (int)jaw_worm_move::bellow;
        else if (chance <= 0.493 + 0.275) current_move = (int)jaw_worm_move::chomp;
        else current_move = (int)jaw_worm_move::thrash;
        break;
    }

    }
}



void jaw_worm::play_turn(playInfo& info){

    switch((jaw_worm_move)current_move){


    case (jaw_worm_move::chomp):{

        perform_attack(info);

        break;
    }


    case (jaw_worm_move::bellow): {

        int effect_number = 3;
        int block_number = 6;

        abstractPower* np = PowerFactory::createPower(powerID::strength, info.attacker, effect_number);
        info.attacker->add_power(info.actions, np);

        perform_block(info, block_number);

        break;
    }


    case (jaw_worm_move::thrash): {

        int block_number = 5;

        perform_attack(info);

        perform_block(info, block_number);

        break;
    }

    }

    enemy_turn++;
    choose_move();
}