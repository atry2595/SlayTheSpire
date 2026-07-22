#ifndef COMBAT_MANAGER_H
#define COMBAT_MANAGER_H

#include <QObject>
#include <vector>
#include "entity/abstractenemy.h"
#include "categories/general.h"
#include "entity/ironclad.h"
#include "combat/combat_event.h"
#include "combatrewards.h"
#include "core/setting.h"

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

    std::unordered_map<ironclad*, combatReward*> rewards;

protected:
    std::vector<ironclad*> players;
    std::vector<bool> player_is_alive = {};
    std::vector<abstractEnemy*> enemies;
    std::vector<bool> enemy_is_alive = {};

    int combat_turn = 1;
    int current_player = 0;

    TurnPhase current_phase = TurnPhase::player;

    CombatType combat_type;

public:
    inline static int reward_card_count = 3;
    inline static int reward_elite_relic_count = 1;

    combat_manager(std::vector<ironclad*> players,
                   std::vector<abstractEnemy*> enemies,
                   CombatType type,
                   combatEvent* eve);

    void combat_start();
    void combat_end();

    bool combat_finished();

    void turn_start();
    void turn_end();
    void next_turn();

    std::vector<ironclad*> get_players() {return players;}
    std::vector<abstractEnemy*> get_enemies() {return enemies;}
    std::vector<bool> get_player_is_alive() { return player_is_alive; }
    std::vector<bool> get_enemy_is_alive() { return enemy_is_alive; }
    CombatType get_type() {return combat_type;}

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

    void calculate_rewards();
    auto get_rewards() { return rewards; }

    combatEvent* get_event() { return event;}

private slots:
    void check_end();

};

#endif // COMBAT_MANAGER_H
