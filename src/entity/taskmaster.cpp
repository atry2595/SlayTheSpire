#include "taskmaster.h"
#include "cards/cardfactory.h"
#include "entity/ironclad.h"

taskmaster::taskmaster(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


taskmaster* taskmaster::create(game_action& actions){

    QString name = tr("Taskmaster");

    RNG& rng = RNG::instance();
    int hp = rng.randint(54, 60);

    taskmaster* enemy = new taskmaster(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Scouring Whip");
    intnt1.type = intent_type::attack_debuff;
    intnt1.damage = 7;

    enemy->intent_list[(int)taskmaster_move::scouring_whip] = intnt1;

    enemy->current_move = (int)taskmaster_move::scouring_whip;

    return enemy;
}



void taskmaster::choose_move() {

}



void taskmaster::play_turn(playInfo& info){

    switch((taskmaster_move)current_move){


    case (taskmaster_move::scouring_whip):{

        perform_attack(info);

        for (auto item : info.target_list) {
            abstractCard* nc = CardFactory::createCard(cardID::wound);
            ironclad* player = dynamic_cast<ironclad*>(item);
            if (!player) continue;
            player->discard_pile_add(nc, true);
        }

        break;
    }


    }

    enemy_turn++;
    choose_move();
}

QString taskmaster::get_story() {
    return (QObject::tr("The Taskmaster cracks his whip over empty chains, bellowing unanswered commands into the deserted streets of the wounded city.\nHis only loyal soldier is the echo off the crumbling walls, saluting him back with his own voice each time."));
}
