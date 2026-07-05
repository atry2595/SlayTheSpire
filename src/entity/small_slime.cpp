#include "small_slime.h"
#include "items/powers/powerfactory.h"

small_slime::small_slime(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


small_slime* small_slime::create(){

    QString name = tr("Small Slime");

    RNG& rng = RNG::instance();
    int hp = rng.randint(8, 12);

    small_slime* enemy = new small_slime(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Lick");
    intnt1.type = intent_type::debuff;

    enemy_intent intnt2;
    intnt2.name = tr("Tackle");
    intnt2.type = intent_type::attack;
    intnt2.damage = 3;

    enemy->intent_list[(int)small_slime_move::lick] = intnt1;
    enemy->intent_list[(int)small_slime_move::tackle] = intnt2;

    if (rng.chance(0.5)) enemy->current_move = (int)small_slime_move::lick;
    else enemy->current_move = (int)small_slime_move::tackle;

    return enemy;
}



void small_slime::choose_move() {
    RNG& rng = RNG::instance();

    if (current_move == (int)small_slime_move::lick) current_move = (int)small_slime_move::tackle;
    else if (rng.chance(0.5)) current_move = (int)small_slime_move::lick;
    else current_move = (int)small_slime_move::tackle;
}



void small_slime::play_turn(playInfo& info){

    switch((small_slime_move)current_move){


    case (small_slime_move::lick):{
        int effect_number = 1;

        for (auto item : info.target_list) {
            abstractPower* np = PowerFactory::createPower(powerID::weak, item, effect_number);
            item->add_power(info.actions, np);
        }

        break;
    }



    case (small_slime_move::tackle): {

        perform_attack(info);

        break;
    }

    }

    enemy_turn++;
    choose_move();
}