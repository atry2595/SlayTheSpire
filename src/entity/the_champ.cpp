#include "the_champ.h"
#include "items/powers/powerfactory.h"

the_champ::the_champ(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


the_champ* the_champ::create(game_action& actions){

    QString name = tr("The Champ");

    RNG& rng = RNG::instance();
    int hp = 420;

    the_champ* enemy = new the_champ(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Heavy Slash");
    intnt1.type = intent_type::attack;
    intnt1.damage = 16;

    enemy_intent intnt2;
    intnt2.name = tr("Face Slap");
    intnt2.type = intent_type::attack_debuff;
    intnt2.damage = 12;


    enemy_intent intnt3;
    intnt3.name = tr("Defensive Stance");
    intnt3.type = intent_type::block_buff;

    enemy_intent intnt4;
    intnt4.name = tr("Gloat");
    intnt4.type = intent_type::debuff;

    enemy_intent intnt5;
    intnt5.name = tr("Taunt");
    intnt5.type = intent_type::special;

    enemy_intent intnt6;
    intnt6.name = tr("Anger");
    intnt6.type = intent_type::buff;

    enemy_intent intnt7;
    intnt7.name = tr("Execute");
    intnt7.type = intent_type::attack;
    intnt7.damage = 10;
    intnt7.repeat = 2;

    enemy->intent_list[(int)the_champ_move::heavy_slash] = intnt1;
    enemy->intent_list[(int)the_champ_move::face_slap] = intnt2;
    enemy->intent_list[(int)the_champ_move::defensive_stance] = intnt3;
    enemy->intent_list[(int)the_champ_move::gloat] = intnt4;
    enemy->intent_list[(int)the_champ_move::taunt] = intnt5;
    enemy->intent_list[(int)the_champ_move::anger] = intnt6;
    enemy->intent_list[(int)the_champ_move::execute] = intnt7;

    enemy->current_move = (int)the_champ_move::taunt;

    return enemy;
}



void the_champ::choose_move() {
    RNG& rng = RNG::instance();

    if (hp <= max_hp/2 && phase == 1){
        phase = 2;
        phase_turn = 0;
    }


    if (phase == 1 && phase_turn % 4 == 0) {

        current_move = (int)the_champ_move::taunt;

    }

    else if (phase == 2 && phase_turn == 0) {

        current_move = (int)the_champ_move::anger;

    }

    else if (phase == 2 && phase_turn % 3 == 1){

        current_move = (int)the_champ_move::execute;

    }

    else {

        switch ((the_champ_move)current_move){

        case (the_champ_move::anger):
        case (the_champ_move::taunt):
        case (the_champ_move::execute): {
            double chance = rng.random();
            if (chance <= 0.15) current_move = (int)the_champ_move::defensive_stance;
            else if (chance <= 0.15 + 0.15) current_move = (int)the_champ_move::gloat;
            else if (chance <= 0.15 + 0.15 + 0.25) current_move = (int)the_champ_move::face_slap;
            else current_move = (int)the_champ_move::heavy_slash;
            break;
        }

        case (the_champ_move::defensive_stance): {
            double chance = rng.random();
            if (chance <= 0.176) current_move = (int)the_champ_move::gloat;
            else if (chance <= 0.176 + 0.294) current_move = (int)the_champ_move::face_slap;
            else current_move = (int)the_champ_move::heavy_slash;
            break;
        }

        case (the_champ_move::gloat): {
            double chance = rng.random();
            if (chance <= 0.176) current_move = (int)the_champ_move::defensive_stance;
            else if (chance <= 0.176 + 0.294) current_move = (int)the_champ_move::face_slap;
            else current_move = (int)the_champ_move::heavy_slash;
            break;
        }

        case (the_champ_move::face_slap): {
            double chance = rng.random();
            if (chance <= 0.2) current_move = (int)the_champ_move::defensive_stance;
            else if (chance <= 0.2 + 0.2) current_move = (int)the_champ_move::gloat;
            else current_move = (int)the_champ_move::heavy_slash;
            break;
        }

        case (the_champ_move::heavy_slash): {
            double chance = rng.random();
            if (chance <= 0.272) current_move = (int)the_champ_move::defensive_stance;
            else if (chance <= 0.272 + 0.272) current_move = (int)the_champ_move::gloat;
            else current_move = (int)the_champ_move::face_slap;
            break;
        }

        }

    }
}



void the_champ::play_turn(playInfo& info){

    switch((the_champ_move)current_move){


    case (the_champ_move::heavy_slash):{

        perform_attack(info);

        break;
    }


    case (the_champ_move::face_slap): {

        int effect_number = 2;

        perform_attack(info);

        for (auto item : info.target_list) {
            abstractPower* np1 = PowerFactory::createPower(powerID::frail, item, effect_number);
            item->add_power(info.actions, np1);
            abstractPower* np2 = PowerFactory::createPower(powerID::vulnerable, item, effect_number);
            item->add_power(info.actions, np2);
        }

        break;
    }

    case (the_champ_move::defensive_stance): {

        int effect_number = 5;
        int block_number = 15;

        perform_block(info, block_number);

        abstractPower* np = PowerFactory::createPower(powerID::metallicize, info.attacker, effect_number);
        info.attacker->add_power(info.actions, np);

        break;
    }

    case (the_champ_move::gloat): {

        int effect_number = 2;

        abstractPower* np = PowerFactory::createPower(powerID::strength, info.attacker, effect_number);
        info.attacker->add_power(info.actions, np);

        break;
    }

    case (the_champ_move::taunt): {

        int effect_number = 2;

        for (auto item : info.target_list) {
            abstractPower* np1 = PowerFactory::createPower(powerID::weak, item, effect_number);
            item->add_power(info.actions, np1);
            abstractPower* np2 = PowerFactory::createPower(powerID::vulnerable, item, effect_number);
            item->add_power(info.actions, np2);
        }

        break;
    }

    case (the_champ_move::anger): {

        int effect_number = 6;

        abstractPower* np = PowerFactory::createPower(powerID::strength, info.attacker, effect_number);
        info.attacker->add_power(info.actions, np);

        auto pow_list = info.attacker->get_power_list();

        for (int i = pow_list.size() - 1; i >= 0; i--){
            if (pow_list[i]->get_is_buff() == false){
                info.attacker->remove_power(pow_list[i]);
            }
        }

        break;
    }

    case (the_champ_move::execute): {

        perform_attack(info);

        break;
    }

    }

    enemy_turn++;
    phase_turn++;
    choose_move();
}