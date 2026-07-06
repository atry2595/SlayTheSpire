#include "medium_slime.h"
#include "items/powers/powerfactory.h"
#include "cards/cardfactory.h"
#include "entity/ironclad.h"

medium_slime::medium_slime(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


medium_slime* medium_slime::create(game_action& actions, int hp){

    QString name = tr("Medium Slime");

    RNG& rng = RNG::instance();
    if (hp == -1) hp = rng.randint(28, 32);

    medium_slime* enemy = new medium_slime(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Lick");
    intnt1.type = intent_type::debuff;

    enemy_intent intnt2;
    intnt2.name = tr("Tackle");
    intnt2.type = intent_type::attack;
    intnt2.damage = 10;

    enemy_intent intnt3;
    intnt3.name = tr("Corrosive Spit");
    intnt3.type = intent_type::attack_debuff;
    intnt3.damage = 7;

    enemy->intent_list[(int)medium_slime_move::lick] = intnt1;
    enemy->intent_list[(int)medium_slime_move::tackle] = intnt2;
    enemy->intent_list[(int)medium_slime_move::corrosive_spit] = intnt3;

    if (rng.chance(0.3)) enemy->current_move = (int)medium_slime_move::corrosive_spit;
    else if (rng.chance(0.3 + 0.4)) enemy->current_move = (int)medium_slime_move::lick;
    else enemy->current_move = (int)medium_slime_move::tackle;

    return enemy;
}



void medium_slime::choose_move() {
    RNG& rng = RNG::instance();

    int temp = current_move;

    if (current_move == (int)medium_slime_move::tackle){
        if (rng.chance(0.5)) current_move = (int)medium_slime_move::corrosive_spit;
        else current_move = (int)medium_slime_move::lick;
    }
    else if (current_move == last_move && current_move == (int)medium_slime_move::lick){
        if (rng.chance(0.571)) current_move = (int)medium_slime_move::tackle;
        else current_move = (int)medium_slime_move::corrosive_spit;
    }
    else if (current_move == last_move && current_move == (int)medium_slime_move::corrosive_spit) {
        if (rng.chance(0.571)) current_move = (int)medium_slime_move::tackle;
        else current_move = (int)medium_slime_move::lick;
    }
    else{
        if (rng.chance(0.3)) current_move = (int)medium_slime_move::corrosive_spit;
        if (rng.chance(0.3 + 0.4)) current_move = (int)medium_slime_move::lick;
        else current_move = (int)medium_slime_move::tackle;
    }

    last_move = temp;
}



void medium_slime::play_turn(playInfo& info){

    switch((medium_slime_move)current_move){


    case (medium_slime_move::lick):{
        int effect_number = 1;

        for (auto item : info.target_list) {
            abstractPower* np = PowerFactory::createPower(powerID::weak, item, effect_number);
            item->add_power(info.actions, np);
        }

        break;
    }



    case (medium_slime_move::tackle): {

        perform_attack(info);

        break;
    }


    case (medium_slime_move::corrosive_spit):{
        perform_attack(info);

        for (auto item : info.target_list) {
            abstractCard* card = CardFactory::createCard(cardID::slimed);
            ironclad* player = dynamic_cast<ironclad*>(item);
            if (player) player->discard_pile_add(card, true);
        }

        break;
    }

    }

    enemy_turn++;
    choose_move();
}