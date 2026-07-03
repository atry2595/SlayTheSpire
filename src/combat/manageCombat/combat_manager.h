#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H

#include <QObject>
#include <vector>
#include "combat_player.h"
#include "entity/abstractenemy.h"
#include "combat/combat_event.h"

enum class TurnPhase{
    player,
    enemy
};

class combat_manager : public QObject
{
    Q_OBJECT

private:
    combatEvent* event;
    game_action actions;

protected:
    std::vector<combat_player*> players;
    std::vector<bool> player_is_alive = {};
    std::vector<abstractEnemy*> enemies;
    std::vector<bool> enemy_is_alive = {};

    int combat_turn = 1;
    int current_player = 0;

    TurnPhase current_phase = TurnPhase::player;

public:

    combat_manager(std::vector<combat_player*> players,
                   std::vector<abstractEnemy*> enemies,
                   combatEvent* eve);

    void combat_start();
    void combat_end();

    bool combat_finished();

    void turn_start();
    void turn_end();
    void next_turn();

    int get_enemy_index(abstractEnemy* enmy){
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i] == enmy) return i;
        }
        return -1;
    }

    void set_enemy_died(abstractEnemy* enmy){
        for (int i = 0; i < enemies.size(); i++) {
            if (enemies[i] == enmy) enemy_is_alive[i] = false;
        }
    }

    combat_player* get_player_by_character(ironclad* chr) {
        for (auto item : players) {
            if (item->get_character() == chr) return item;
        }
        return nullptr;
    }

    void add_enemy(abstractEnemy*, int);
};

#endif // COMBAT_MANAGER_H
