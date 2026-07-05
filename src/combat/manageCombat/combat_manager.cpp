#include "combat_manager.h"
#include "combat/game_action.h"
#include "combat/play_info.h"

combat_manager::combat_manager(std::vector<ironclad*> players_init,
               std::vector<abstractEnemy*> enemies_init,
                               combatEvent* eve)
    :players(players_init),
    enemies(enemies_init),
    event(eve),
    actions(game_action(eve))
{
    for (int i = 0; i < players.size(); i++) player_is_alive.push_back(players[i]->get_hp() > 0);
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

}

void combat_manager::combat_start() {

    combat_turn = 1;
    current_player = 0;
    current_phase = TurnPhase::player;

    emit event->combat_started();


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

            emit event->turn_started(players[current_player]);

            players[current_player]->at_turn_start(actions);
            // play + trun end
            // timer
        }
    }

    else {
        for (int i = 0; i<enemies.size(); i++) {

            if (!enemy_is_alive[i]){
                continue;
            }

            emit event->turn_started(enemies[i]);


            enemies[i]->at_turn_start(actions);


            std::vector<abstractEntity*> trg;
            for (auto item : players) trg.push_back(item);

            playInfo info(actions);
            info.attacker = enemies[i];
            info.target_list = trg;

            enemies[i]->play_turn(info);
        }

        turn_end();
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


            players[current_player]->at_turn_end(actions);

            emit event->turn_ended(players[current_player]);

            players[current_player]->turn_reset();
        }
    }

    else {
        auto enemies_copy = enemies;

        for (int i = 0; i<enemies_copy.size(); i++) {

            if (!enemy_is_alive[i]){
                continue;
            }

            enemies_copy[i]->at_turn_end(actions);

            emit event->turn_ended(enemies_copy[i]);

            enemies_copy[i]->turn_reset();
        }
    }

    next_turn();

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

    emit event->combat_ended(victory);

}



void combat_manager::next_turn() {

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

