#include "large_slime.h"
#include "medium_slime.h"
#include "items/powers/powerfactory.h"
#include "cards/cardfactory.h"
#include "entity/ironclad.h"

large_slime::large_slime(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


large_slime* large_slime::create(game_action& actions, int hp){

    QString name = tr("Large Slime");

    RNG& rng = RNG::instance();
    if(hp == -1) hp = rng.randint(65, 69);

    large_slime* enemy = new large_slime(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Lick");
    intnt1.type = intent_type::debuff;

    enemy_intent intnt2;
    intnt2.name = tr("Tackle");
    intnt2.type = intent_type::attack;
    intnt2.damage = 16;

    enemy_intent intnt3;
    intnt3.name = tr("Corrosive Spit");
    intnt3.type = intent_type::attack_debuff;
    intnt3.damage = 11;

    enemy_intent intnt4;
    intnt4.name = tr("Split");
    intnt4.type = intent_type::special;

    enemy->intent_list[(int)large_slime_move::lick] = intnt1;
    enemy->intent_list[(int)large_slime_move::tackle] = intnt2;
    enemy->intent_list[(int)large_slime_move::corrosive_spit] = intnt3;
    enemy->intent_list[(int)large_slime_move::split] = intnt4;

    if (rng.chance(0.3)) enemy->current_move = (int)large_slime_move::corrosive_spit;
    else if (rng.chance(0.3 + 0.4)) enemy->current_move = (int)large_slime_move::lick;
    else enemy->current_move = (int)large_slime_move::tackle;

    enemy->half_hp_connection = connect(actions.get_event(), &combatEvent::hp_changed, enemy,
        [enemy](abstractEntity* entity, int oldHP, int newHP){
            if (enemy == entity){
                if (newHP < enemy->get_max_hp() / 2){
                    enemy->last_move = -1;
                    enemy->current_move = (int)large_slime_move::split;
                    disconnect(enemy->half_hp_connection);
                }
            }
    });


    return enemy;
}



void large_slime::choose_move() {
    RNG& rng = RNG::instance();

    if (current_move == (int)large_slime_move::split) return;

    int temp = current_move;

    if (current_move == (int)large_slime_move::tackle){
        if (rng.chance(0.5)) current_move = (int)large_slime_move::corrosive_spit;
        else current_move = (int)large_slime_move::lick;
    }
    else if (current_move == last_move && current_move == (int)large_slime_move::lick){
        if (rng.chance(0.571)) current_move = (int)large_slime_move::tackle;
        else current_move = (int)large_slime_move::corrosive_spit;
    }
    else if (current_move == last_move && current_move == (int)large_slime_move::corrosive_spit) {
        if (rng.chance(0.571)) current_move = (int)large_slime_move::tackle;
        else current_move = (int)large_slime_move::lick;
    }
    else{
        if (rng.chance(0.3)) current_move = (int)large_slime_move::corrosive_spit;
        if (rng.chance(0.3 + 0.4)) current_move = (int)large_slime_move::lick;
        else current_move = (int)large_slime_move::tackle;
    }

    last_move = temp;
}



void large_slime::play_turn(playInfo& info){

    switch((large_slime_move)current_move){


    case (large_slime_move::lick):{
        int effect_number = 2;

        for (auto item : info.target_list) {
            abstractPower* np = PowerFactory::createPower(powerID::weak, item, effect_number);
            item->add_power(info.actions, np);
        }

        break;
    }



    case (large_slime_move::tackle): {

        perform_attack(info);

        break;
    }


    case (large_slime_move::corrosive_spit):{
        perform_attack(info);

        for (auto item : info.target_list) {
            abstractCard* card1 = CardFactory::createCard(cardID::slimed);
            abstractCard* card2 = CardFactory::createCard(cardID::slimed);
            ironclad* player = dynamic_cast<ironclad*>(item);
            if (player) player->discard_pile_add(card1);
            if (player) player->discard_pile_add(card2);
        }

        break;
    }


    case (large_slime_move::split):{
        medium_slime* ms1 = medium_slime::create(info.actions, this->hp);
        medium_slime* ms2 = medium_slime::create(info.actions, this->hp);

        info.actions.get_event()->entity_add_before(ms1, this);
        info.actions.get_event()->entity_add_after(ms2, this);
        info.actions.get_event()->entity_removed(this);
        return;
    }


    }

    enemy_turn++;
    choose_move();
}