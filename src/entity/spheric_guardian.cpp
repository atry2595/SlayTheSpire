#include "spheric_guardian.h"
#include "items/powers/powerfactory.h"

spheric_guardian::spheric_guardian(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


spheric_guardian* spheric_guardian::create(game_action& actions){

    QString name = tr("Spheric Guardian");

    RNG& rng = RNG::instance();
    int hp = 20;

    spheric_guardian* enemy = new spheric_guardian(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Activate");
    intnt1.type = intent_type::block;

    enemy_intent intnt2;
    intnt2.name = tr("Debuff Attack");
    intnt2.type = intent_type::attack_debuff;
    intnt2.damage = 10;


    enemy_intent intnt3;
    intnt3.name = tr("Slam");
    intnt3.type = intent_type::attack;
    intnt3.damage = 10;
    intnt3.repeat = 2;

    enemy_intent intnt4;
    intnt4.name = tr("Harden");
    intnt4.type = intent_type::attack_block;
    intnt4.damage=10;

    enemy->intent_list[(int)spheric_guardian_move::activate] = intnt1;
    enemy->intent_list[(int)spheric_guardian_move::debuff_attack] = intnt2;
    enemy->intent_list[(int)spheric_guardian_move::slam] = intnt3;
    enemy->intent_list[(int)spheric_guardian_move::harden] = intnt4;

    enemy->current_move = (int)spheric_guardian_move::activate;
    enemy->set_block(40);
    abstractPower* p = PowerFactory::createPower(powerID::barricade, enemy, 1);
    enemy->add_power(actions, p);

    return enemy;
}



void spheric_guardian::choose_move() {
    RNG& rng = RNG::instance();

    switch((spheric_guardian_move)current_move){

    case (spheric_guardian_move::activate):{
        current_move = (int)spheric_guardian_move::debuff_attack;
        break;
    }

    case (spheric_guardian_move::debuff_attack):
    case (spheric_guardian_move::harden): {
        current_move = (int)spheric_guardian_move::slam;
        break;
    }

    case (spheric_guardian_move::slam): {
        current_move = (int)spheric_guardian_move::harden;
        break;
    }

    }
}



void spheric_guardian::play_turn(playInfo& info){

    switch((spheric_guardian_move)current_move){


    case (spheric_guardian_move::activate):{

        int block_number = 25;
        perform_block(info, block_number);

        break;
    }


    case (spheric_guardian_move::debuff_attack): {

        int effect_number = 5;

        perform_attack(info);

        for (auto item : info.target_list) {
            abstractPower* np = PowerFactory::createPower(powerID::frail, item, effect_number);
            item->add_power(info.actions, np);
        }

        break;
    }

    case (spheric_guardian_move::slam): {

        perform_attack(info);

        break;
    }

    case (spheric_guardian_move::harden): {

        int block_number = 25;
        perform_block(info, block_number);

        perform_attack(info);

        break;
    }

    }

    enemy_turn++;
    choose_move();
}

QString spheric_guardian::get_story() {
    return (QObject::tr("The Spheric Guardian hovers in the forgotten corridor, its armor contracting and expanding with a metallic breath.\nIt guards nothing but a fading memory of an order that will never arrive, forever wandering between attack and defense."));
}
