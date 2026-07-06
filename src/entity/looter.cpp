#include "looter.h"
#include "items/powers/powerfactory.h"

looter::looter(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


looter* looter::create(game_action& actions){

    QString name = tr("Looter");

    RNG& rng = RNG::instance();
    int hp = rng.randint(44, 48);

    looter* enemy = new looter(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Mug");
    intnt1.type = intent_type::attack;
    intnt1.damage = 10;

    enemy_intent intnt2;
    intnt2.name = tr("Lunge");
    intnt2.type = intent_type::attack;
    intnt2.damage = 12;

    enemy_intent intnt3;
    intnt3.name = tr("Smoke Bomb");
    intnt3.type = intent_type::block;

    enemy_intent intnt4;
    intnt4.name = tr("Escape");
    intnt4.type = intent_type::special;


    enemy->intent_list[(int)looter_move::mug] = intnt1;
    enemy->intent_list[(int)looter_move::lunge] = intnt2;
    enemy->intent_list[(int)looter_move::smoke_bombe] = intnt3;
    enemy->intent_list[(int)looter_move::escape] = intnt4;

    enemy->current_move = (int)looter_move::mug;

    abstractPower* p = PowerFactory::createPower(powerID::thievery, enemy, 1);
    enemy->add_power(actions, p);

    return enemy;
}



void looter::choose_move() {
    int tmp = current_move;
    
    if (current_move == last_move && current_move == (int)looter_move::mug){
        if (RNG::instance().chance(0.5)) current_move = (int)looter_move::lunge;
        else current_move = (int)looter_move::smoke_bombe;
    }
    else if (current_move == (int)looter_move::mug){
        current_move = (int)looter_move::mug;
    }
    else if (current_move == (int)looter_move::lunge) current_move = (int)looter_move::smoke_bombe;
    else {
        current_move = (int)looter_move::escape;
    }

    last_move = tmp;
}



void looter::play_turn(playInfo& info){

    switch((looter_move)current_move){


    case (looter_move::mug):
    case (looter_move::lunge):{

        perform_attack(info);

        break;
    }

    case (looter_move::smoke_bombe):{
        int block_count = 6;

        blockingInfo bl;
        bl.block = block_count;
        bl.owner = this;

        info.actions.apply_block(bl);

        break;
    }

    case (looter_move::escape):{
        emit info.actions.get_event()->entity_escape(this);
        emit info.actions.get_event()->entity_removed(this);
        return;
    }

    }

    enemy_turn++;
    choose_move();
}