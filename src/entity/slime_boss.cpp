#include "slime_boss.h"
#include "large_slime.h"
#include "cards/cardfactory.h"
#include "entity/ironclad.h"

slime_boss::slime_boss(QString name_init, int base_max_hp_init)
    :abstractEnemy(name_init, base_max_hp_init)
{}


slime_boss* slime_boss::create(game_action& actions){

    QString name = tr("Slime Boss");

    RNG& rng = RNG::instance();
    int hp = 140;

    slime_boss* enemy = new slime_boss(name, hp);

    enemy_intent intnt1;
    intnt1.name = tr("Goop Spray");
    intnt1.type = intent_type::debuff;

    enemy_intent intnt2;
    intnt2.name = tr("Preparing");
    intnt2.type = intent_type::special;

    enemy_intent intnt3;
    intnt3.name = tr("Slam");
    intnt3.type = intent_type::attack;
    intnt3.damage = 35;

    enemy_intent intnt4;
    intnt4.name = tr("Split");
    intnt4.type = intent_type::special;

    enemy->intent_list[(int)slime_boss_move::goop_spray] = intnt1;
    enemy->intent_list[(int)slime_boss_move::preparing] = intnt2;
    enemy->intent_list[(int)slime_boss_move::slam] = intnt3;
    enemy->intent_list[(int)slime_boss_move::split] = intnt4;

    enemy->current_move = (int)slime_boss_move::goop_spray;

    enemy->half_hp_connection = connect(actions.get_event(), &combatEvent::hp_changed, enemy,
        [enemy](abstractEntity* entity, int oldHP, int newHP){
            if (enemy == entity){
                if (newHP < enemy->get_max_hp() / 2){
                    enemy->last_move = -1;
                    enemy->current_move = (int)slime_boss_move::split;
                    disconnect(enemy->half_hp_connection);
                }
            }
    });


    return enemy;
}



void slime_boss::choose_move() {
    RNG& rng = RNG::instance();

    if (current_move == (int)slime_boss_move::split) return;

    switch((slime_boss_move)current_move){
    case slime_boss_move::goop_spray:
        current_move = (int)slime_boss_move::preparing;
        break;
    case slime_boss_move::preparing:
        current_move = (int)slime_boss_move::slam;
        break;
    case slime_boss_move::slam:
        current_move = (int)slime_boss_move::goop_spray;
        break;
    default:
        break;
    }
}



void slime_boss::play_turn(playInfo& info){

    switch((slime_boss_move)current_move){


    case (slime_boss_move::goop_spray):{

        for (auto item : info.target_list) {
            abstractCard* card1 = CardFactory::createCard(cardID::slimed);
            abstractCard* card2 = CardFactory::createCard(cardID::slimed);
            abstractCard* card3 = CardFactory::createCard(cardID::slimed);
            ironclad* player = dynamic_cast<ironclad*>(item);
            if (player) player->discard_pile_add(card1, true);
            if (player) player->discard_pile_add(card2, true);
            if (player) player->discard_pile_add(card3, true);
        }

        break;
    }



    case (slime_boss_move::preparing): {
        break;
    }


    case (slime_boss_move::slam):{
        perform_attack(info);

        break;
    }


    case (slime_boss_move::split):{
        large_slime* ms1 = large_slime::create(info.actions, this->hp);
        large_slime* ms2 = large_slime::create(info.actions, this->hp);

        info.actions.get_event()->entity_add_before(ms1, this);
        info.actions.get_event()->entity_add_after(ms2, this);
        hp = 0;
        emit info.actions.get_event()->entity_removed(this);
        emit info.actions.get_event()->resetLayout();
        return;
    }


    }

    enemy_turn++;
    choose_move();
}