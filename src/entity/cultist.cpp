#include "cultist.h"
#include "items/powers/powerfactory.h"

cultist::cultist(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


cultist* cultist::create(){

    QString name = tr("Cultist");

    RNG& rng = RNG::instance();
    int hp = rng.randint(48, 54);

    cultist* enemy = new cultist(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Incantation");
    intnt1.type = intent_type::buff;

    enemy_intent intnt2;
    intnt2.name = tr("Dark Strike");
    intnt2.type = intent_type::attack;
    intnt2.damage = 6;

    enemy->intent_list[(int)cultist_move::incantation] = intnt1;
    enemy->intent_list[(int)cultist_move::dark_strike] = intnt2;

    enemy->current_move = (int)cultist_move::incantation;

    return enemy;
}



void cultist::choose_move() {
    current_move = (int)cultist_move::dark_strike;
}



void cultist::play_turn(playInfo& info){

    switch((cultist_move)current_move){


    case (cultist_move::incantation):{
        int effect_number = 3;

        abstractPower* np = PowerFactory::createPower(powerID::ritual, info.attacker, effect_number);
        info.attacker->add_power(np);
        break;
    }



    case (cultist_move::dark_strike): {

        enemy_intent& intnt = intent_list.at(current_move);

        attackInfo atck_info;
        atck_info.attacker = info.attacker;
        atck_info.target_list = info.target_list;
        atck_info.damage = intnt.damage;

        for (int i = 0 ; i<intnt.repeat; i++) {
            info.actions.attack(atck_info);
        }
        break;
    }

    }

    enemy_turn++;
    choose_move();
}