#include "combat_manager.h"
#include "combat/game_action.h"
#include "combat/play_info.h"
#include "items/potions/potionfactory.h"
#include "items/relics/relicfactory.h"
#include "cards/cardfactory.h"
#include <QTimer>

combat_manager::combat_manager(std::vector<ironclad*> players_init,
                               std::vector<abstractEnemy*> enemies_init,
                               CombatType type, combatEvent* eve)
    :players(players_init),
    enemies(enemies_init),
    combat_type(type),
    event(eve),
    actions(game_action(eve))
{
    for (int i = 0; i < players.size(); i++) {
        player_is_alive.push_back(players[i]->get_hp() > 0);
    }
    for (int i = 0; i < enemies.size(); i++) enemy_is_alive.push_back(true);

    remove_connection = connect(event, &combatEvent::entity_removed, this,
                                [this](abstractEntity* entity){
                                    for (int i = 0; i < players.size(); i++){
                                        if (players[i] == entity){
                                            player_is_alive[i] = false;
                                        }
                                    }

                                    for (int i = 0; i < enemies.size(); i++){
                                        if (enemies[i] == entity){
                                            enemy_is_alive[i] = false;
                                        }
                                    }
                                });

    add_after_connection = connect(event, &combatEvent::entity_add_after, this,
                                   [this](abstractEntity* entity, abstractEntity* after){
                                       abstractEnemy* after_as_enemy = dynamic_cast<abstractEnemy*>(after);
                                       abstractEnemy* entity_as_enemy = dynamic_cast<abstractEnemy*>(entity);
                                       if (after_as_enemy == nullptr || entity_as_enemy == nullptr) return;

                                       int ind = get_enemy_index(after_as_enemy);
                                       if (ind == -1) return;

                                       add_enemy(entity_as_enemy, ind+1);

                                   });

    add_before_connection = connect(event, &combatEvent::entity_add_before, this,
                                    [this](abstractEntity* entity, abstractEntity* before){
                                        abstractEnemy* before_as_enemy = dynamic_cast<abstractEnemy*>(before);
                                        abstractEnemy* entity_as_enemy = dynamic_cast<abstractEnemy*>(entity);
                                        if (before_as_enemy == nullptr || entity_as_enemy == nullptr) return;

                                        int ind = get_enemy_index(before_as_enemy);
                                        if (ind == -1) return;

                                        add_enemy(entity_as_enemy, ind);

                                    });


    connect(event, &combatEvent::turn_ended, this, [=](abstractEntity*){
        if (!combat_finished())next_turn();
    });
    connect(event, &combatEvent::entity_removed, this, &combat_manager::check_end);
    connect(event, &combatEvent::entity_escape, this, &combat_manager::check_end);

}

void combat_manager::combat_start() {

    combat_turn = 1;
    current_player = 0;
    current_phase = TurnPhase::player;

    emit event->combat_started(this);


    for (int i = 0; i < players.size(); i++) {
        if (!player_is_alive[i]) continue;

        players[i]->at_combat_start(actions);
    }

    for (auto item : enemies) item->at_combat_start(actions);


    turn_start();
}



void combat_manager::turn_start() {

    if (current_phase == TurnPhase::player) {
        if (current_player < players.size()) {

            if (!player_is_alive[current_player]){
                turn_end();
                return;
            }

            players[current_player]->at_turn_start(actions);

            emit event->turn_started(players[current_player]);

            // play + trun end
            // timer
            return;
        }
    }

    else {
        for (int i = 0; i<enemies.size(); i++) {
            if (!enemy_is_alive[i]){
                continue;
            }

            QTimer::singleShot(500, [=](){

                emit event->turn_started(enemies[i]);


                enemies[i]->at_turn_start(actions);


                std::vector<abstractEntity*> trg;
                for (auto item : players) trg.push_back(item);

                playInfo info(actions);
                info.attacker = enemies[i];
                info.target_list = trg;

                enemies[i]->play_turn(info);
            });

        }
        QTimer::singleShot(enemies.size()*1000, [this](){turn_end();});
    }
}


void combat_manager::turn_end() {



    if (current_phase == TurnPhase::player) {
        if (current_player < players.size()) {

            if (!player_is_alive[current_player]){
                next_turn();
                return;
            }

        }
    }

    else {
        auto enemies_copy = enemies;

        for (int i = 0; i<enemies_copy.size(); i++) {

            if (!enemy_is_alive[i]){
                continue;
            }

            enemies_copy[i]->at_turn_end(actions);


            enemies_copy[i]->turn_reset();
        }
    }

    emit event->turn_ended(enemies[0]);

}



void combat_manager::combat_end() {

    bool victory = false;

    for (int i = 0; i < players.size(); i++){
        victory |= player_is_alive[i];

        if (player_is_alive[i]) {
            players[i]->at_combat_end(actions);
            players[i]->combat_reset();
        }
    }

    calculate_rewards();

    emit event->combat_ended(this, victory);

}



void combat_manager::next_turn() {

    if (current_phase == TurnPhase::player) {
        players[current_player]->at_turn_end(actions);
        players[current_player]->turn_reset();
    }

    if (current_phase == TurnPhase::player && current_player + 1 < players.size()) current_player++;

    else if (current_phase == TurnPhase::player && current_player + 1 >= players.size()) {
        current_player = 0;
        current_phase = TurnPhase::enemy;
    }

    else {
        current_phase = TurnPhase::player;
        combat_turn++;
    }

    turn_start();
}



bool combat_manager::combat_finished() {
    bool all_players = false;
    bool all_enemy = false;

    for (int i = 0 ; i<players.size(); i++){
        player_is_alive[i] = (players[i]->get_hp() > 0);
        all_players |= player_is_alive[i];
    }

    for (int i = 0 ; i<enemies.size(); i++){
        enemy_is_alive[i] = (enemies[i]->get_hp() > 0);
        all_enemy |= enemy_is_alive[i];
    }

    return !(all_players && all_enemy);
}



void combat_manager::add_enemy(abstractEnemy* enmy, int index){
    enemies.insert(enemies.begin() + index, enmy);
    enemy_is_alive.insert(enemy_is_alive.begin() + index, true);
    enmy->at_combat_start(actions);
}


void combat_manager::calculate_rewards() {
    RNG& rng = RNG::instance();



    std::vector<relicID> rares = rare_relic;
    std::vector<relicID> uncommons = uncommon_relic;
    std::vector<relicID> commons = common_relic;



    for (int i = 0; i<players.size(); i++){

        if (player_is_alive[i] == false) continue;

        combatReward* rew = new combatReward();
        std::vector<relicID> rlcs;
        std::vector<cardID> crds;

        switch(combat_type) {

        case(CombatType::monster):{
            rew->add_gold(rng.randint(15, 25));

            if (rng.chance(0.3)) {
                std::vector<potionID> pot_vec;
                if (rng.chance(0.1)) pot_vec = rare_potions;
                else if (rng.chance(0.1 + 0.15)) pot_vec = uncommon_potions;
                else pot_vec = common_potions;
                potionID np = rng.choice(pot_vec);
                rew->add_potion(PotionFactory::createPotion(np, players[i]));
            }

            std::vector<double> w;
            for (auto item : non_rare_cards){
                crds.push_back(item);
                w.push_back(1);
            }
            for (auto item : rare_cards) {
                crds.push_back(item);
                w.push_back(7);
            }

            auto selected = rng.weighted_sample(crds, w, reward_card_count);
            std::vector<abstractCard*> to_cards;

            for (auto item : selected){
                abstractCard* created_card = CardFactory::createCard(item);
                if (rng.chance(combat_data::floor / 75.0)) created_card->base_upgrade();
                to_cards.push_back(created_card);
            }
            rew->add_cards(to_cards);

            break;
        }

        case(CombatType::elite):{
            rew->add_gold(rng.randint(15, 25));

            if (rng.chance(0.4)) {
                std::vector<potionID> pot_vec;
                if (rng.chance(0.15)) pot_vec = rare_potions;
                else if (rng.chance(0.15 + 0.18)) pot_vec = uncommon_potions;
                else pot_vec = common_potions;
                potionID np = rng.choice(pot_vec);
                rew->add_potion(PotionFactory::createPotion(np, players[i]));
            }

            std::vector<double> w;
            for (auto item : non_rare_cards){
                crds.push_back(item);
                w.push_back(1);
            }
            for (auto item : rare_cards) {
                crds.push_back(item);
                w.push_back(5);
            }

            auto selected = rng.weighted_sample(crds, w, reward_card_count);
            std::vector<abstractCard*> to_cards;

            for (auto item : selected){
                abstractCard* created_card = CardFactory::createCard(item);
                if (rng.chance(combat_data::floor / 50.0)) created_card->base_upgrade();
                to_cards.push_back(created_card);
            }
            rew->add_cards(to_cards);


            std::vector<double> wei;
            for (auto item : common_relic){
                if (!players[i]->get_spec_relic(item)) continue;
                rlcs.push_back(item);
                wei.push_back(6);
            }
            for (auto item : uncommon_relic) {
                if (!players[i]->get_spec_relic(item)) continue;
                rlcs.push_back(item);
                wei.push_back(3);
            }
            for (auto item : rare_relic) {
                if (!players[i]->get_spec_relic(item)) continue;
                rlcs.push_back(item);
                wei.push_back(1);
            }

            auto selected2 = rng.weighted_sample(rlcs, wei, reward_elite_relic_count);;

            for (auto item : selected2){
                abstractRelic* created_relic = RelicFactory::createRelic(item, players[i]);
                rew->add_relic(created_relic);
            }



            break;
        }

        case(CombatType::boss):{
            rew->add_gold(80);

            if (rng.chance(0.6)) {
                std::vector<potionID> pot_vec;
                if (rng.chance(0.2)) pot_vec = rare_potions;
                else if (rng.chance(0.2 + 0.3)) pot_vec = uncommon_potions;
                else pot_vec = common_potions;
                potionID np = rng.choice(pot_vec);
                rew->add_potion(PotionFactory::createPotion(np, players[i]));
            }

            crds = rare_cards;

            auto selected = rng.sample(crds, reward_card_count);
            std::vector<abstractCard*> to_cards;

            for (auto item : selected){
                abstractCard* created_card = CardFactory::createCard(item);
                if (rng.chance(combat_data::floor / 75.0)) created_card->base_upgrade();
                to_cards.push_back(created_card);
            }
            rew->add_cards(to_cards);

            break;
        }

        default:
            break;
        }

        rewards[players[i]] = rew;
    }
}


void combat_manager::check_end() {
    if (combat_finished()) {
        combat_end();
    }
}

