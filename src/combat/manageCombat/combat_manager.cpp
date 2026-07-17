#include "combat_manager.h"
#include "combat/game_action.h"
#include "combat/play_info.h"
#include "items/potions/potionfactory.h"
#include "items/relics/relicfactory.h"
#include "cards/cardfactory.h"
#include <QTimer>

combat_manager::combat_manager(std::vector<ironclad*> players_init,
                               std::vector<abstractEnemy*> enemies_init,
                               entityType type, combatEvent* eve)
    :players(players_init),
    enemies(enemies_init),
    combat_type(type),
    event(eve),
    actions(game_action(eve))
{
    for (int i = 0; i < players.size(); i++) {
        player_is_alive.push_back(players[i]->get_hp() > 0);
        rewards.push_back({});
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
        next_turn();
    });

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


    if (combat_finished()){
        combat_end();
        return;
    }

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



void combat_manager::add_returned_coin_reward(abstractEntity* player, int coin) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] == player && player_is_alive[i]) {
            rewards[i].returned_coin += coin;
            return;
        }
    }
}

void combat_manager::add_coin_to_reward(abstractEntity* player, int coin) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] == player && player_is_alive[i]) {
            rewards[i].coin += coin;
            return;
        }
    }
}

void combat_manager::add_card_to_reward(abstractEntity* player, abstractCard* card) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] == player && player_is_alive[i]) {
            rewards[i].card.push_back(card);
            return;
        }
    }
}

void combat_manager::add_relic_to_reward(abstractEntity* player, abstractRelic* relic) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] == player && player_is_alive[i]) {
            rewards[i].relic.push_back(relic);
            return;
        }
    }
}

void combat_manager::add_potion_to_reward(abstractEntity* player, abstractPotion* potion) {
    for (size_t i = 0; i < players.size(); ++i) {
        if (players[i] == player && player_is_alive[i]) {
            rewards[i].potion.push_back(potion);
            return;
        }
    }
}


void combat_manager::calculate_rewards() {
    RNG& rng = RNG::instance();



    std::vector<relicID> rares = rare_relic;
    std::vector<relicID> uncommons = uncommon_relic;
    std::vector<relicID> commons = common_relic;

    rng.shuffle(rares);
    rng.shuffle(uncommons);
    rng.shuffle(commons);

    std::vector<relicID> selected;
    auto take_from_pool = [&](std::vector<relicID>& pool, abstractEntity* player) -> bool {
        for (auto item : pool) {

            if (player->get_spec_relic(item) != nullptr)
                continue;

            if (std::find(selected.begin(), selected.end(), item) != selected.end())
                continue;

            selected.push_back(item);
            return true;
        }
        return false;
    };



    for (int i = 0; i<players.size(); i++){

        if (player_is_alive[i] == false) continue;


        switch(combat_type){

        case(entityType::monster):{
            add_coin_to_reward(players[i], rng.randint(15, 25));

            if (rng.chance(0.3)) {
                auto pot_vec = common_potions;
                potionID np = rng.choice(pot_vec);
                add_potion_to_reward(players[i], PotionFactory::createPotion(np, players[i]));
            }

            for (int j = 0; j<3; j++){
                auto card_vec = non_rare_cards;
                abstractCard* nc = CardFactory::createCard(rng.choice(card_vec));
                if (rng.chance(0.1)) nc->base_upgrade();
                add_card_to_reward(players[i], nc);
            }

            break;
        }

        case(entityType::elite):{
            add_coin_to_reward(players[i], rng.randint(30, 40));

            if (rng.chance(0.6)) {
                auto pot_vec = common_potions;
                if (rng.chance(0.4)) pot_vec = uncommon_potions;
                if (rng.chance(0.05)) pot_vec = rare_potions;

                potionID np = rng.choice(pot_vec);
                add_potion_to_reward(players[i], PotionFactory::createPotion(np, players[i]));
            }

            for (int j = 0; j<3; j++){
                auto card_vec = non_rare_cards;
                abstractCard* nc = CardFactory::createCard(rng.choice(card_vec));
                if (rng.chance(0.33)) nc->base_upgrade();
                add_card_to_reward(players[i], nc);
            }

            selected.clear();
            {
                if (rng.chance(0.4)) {
                    if (!take_from_pool(uncommons, players[i]))
                        take_from_pool(commons, players[i]);
                }

                else {
                    take_from_pool(commons, players[i]);
                }

                add_relic_to_reward(players[i], RelicFactory::createRelic(selected[0], players[i]));
            }

            break;
        }

        case(entityType::boss):{
            add_coin_to_reward(players[i], 80);

            if (rng.chance(0.8)) {
                auto pot_vec = common_potions;
                if (rng.chance(0.4)) pot_vec = uncommon_potions;
                if (rng.chance(0.15)) pot_vec = rare_potions;

                potionID np = rng.choice(pot_vec);
                add_potion_to_reward(players[i], PotionFactory::createPotion(np, players[i]));
            }

            for (int j = 0; j<3; j++){
                auto card_vec = rare_cards;
                abstractCard* nc = CardFactory::createCard(rng.choice(card_vec));
                if (rng.chance(0.15)) nc->base_upgrade();
                add_card_to_reward(players[i], nc);
            }


            selected.clear();
            for (int j = 0; j<3; j++){
                if (!take_from_pool(rares, players[i]))
                    if (!take_from_pool(uncommons, players[i]))
                        take_from_pool(commons, players[i]);

                add_relic_to_reward(players[i], RelicFactory::createRelic(selected[j], players[i]));
            }

            break;
        }

        default:
            break;
        }
    }
}




