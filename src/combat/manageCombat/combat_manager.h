#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H

#include <QObject>
#include <vector>
#include "entity/abstractenemy.h"
#include "entity/ironclad.h"
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
    std::vector<ironclad*> players;
    std::vector<bool> player_is_alive = {};
    std::vector<abstractEnemy*> enemies;
    std::vector<bool> enemy_is_alive = {};

    int combat_turn = 1;
    int current_player = 0;

    TurnPhase current_phase = TurnPhase::player;

public:

    combat_manager(std::vector<ironclad*> players,
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

    void add_enemy(abstractEnemy*, int);
};

#endif // COMBAT_MANAGER_H
