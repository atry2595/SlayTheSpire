#include "mugger.h"
#include "items/powers/powerfactory.h"

mugger::mugger(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


mugger* mugger::create(game_action& actions){

    QString name = tr("Mugger");

    RNG& rng = RNG::instance();
    int hp = rng.randint(48, 52);

    mugger* enemy = new mugger(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Mug");
    intnt1.type = intent_type::attack;
    intnt1.damage = 10;

    enemy_intent intnt2;
    intnt2.name = tr("Lunge");
    intnt2.type = intent_type::attack;
    intnt2.damage = 16;

    enemy_intent intnt3;
    intnt3.name = tr("Smoke Bomb");
    intnt3.type = intent_type::block;

    enemy_intent intnt4;
    intnt4.name = tr("Escape");
    intnt4.type = intent_type::escape;


    enemy->intent_list[(int)mugger_move::mug] = intnt1;
    enemy->intent_list[(int)mugger_move::lunge] = intnt2;
    enemy->intent_list[(int)mugger_move::smoke_bomb] = intnt3;
    enemy->intent_list[(int)mugger_move::escape] = intnt4;

    enemy->current_move = (int)mugger_move::mug;

    abstractPower* p = PowerFactory::createPower(powerID::thievery, enemy, 20);
    enemy->add_power(actions, p);

    return enemy;
}



void mugger::choose_move() {
    int tmp = current_move;
    
    if (current_move == last_move && current_move == (int)mugger_move::mug){
        if (RNG::instance().chance(0.5)) current_move = (int)mugger_move::lunge;
        else current_move = (int)mugger_move::smoke_bomb;
    }
    else if (current_move == (int)mugger_move::mug){
        current_move = (int)mugger_move::mug;
    }
    else if (current_move == (int)mugger_move::lunge) current_move = (int)mugger_move::smoke_bomb;
    else {
        current_move = (int)mugger_move::escape;
    }

    last_move = tmp;
}



void mugger::play_turn(playInfo& info){

    switch((mugger_move)current_move){


    case (mugger_move::mug):
    case (mugger_move::lunge):{

        perform_attack(info);

        break;
    }

    case (mugger_move::smoke_bomb):{
        int block_count = 11;

        blockingInfo bl;
        bl.block = block_count;
        bl.owner = this;

        info.actions.apply_block(bl);

        break;
    }

    case (mugger_move::escape):{
        emit info.actions.get_event()->entity_escape(this);
        emit info.actions.get_event()->entity_removed(this);
        return;
    }

    }

    enemy_turn++;
    choose_move();
}