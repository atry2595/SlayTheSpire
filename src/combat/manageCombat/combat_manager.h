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

    QMetaObject::Connection remove_connection;
    QMetaObject::Connection add_after_connection;
    QMetaObject::Connection add_before_connection;

protected:
    std::vector<ironclad*> players;
    std::vector<bool> player_is_alive = {};
    std::vector<abstractEnemy*> enemies;
    std::vector<bool> enemy_is_alive = {};

    int combat_turn = 1;
    int current_player = 0;

    TurnPhase current_phase = TurnPhase::player;

    entityType combat_type;

public:

    combat_manager(std::vector<ironclad*> players,
                   std::vector<abstractEnemy*> enemies,
                   entityType type,
                   combatEvent* eve);

    void combat_start();
    void combat_end();

    bool combat_finished();

    void turn_start();
    void turn_end();
    void next_turn();

    std::vector<ironclad*> get_players() {return players;}
    std::vector<abstractEnemy*> get_enemies() {return enemies;}
    entityType get_type() {return combat_type;}

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
