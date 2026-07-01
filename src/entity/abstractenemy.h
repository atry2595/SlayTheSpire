#ifndef ABSTRACTENEMY_H
#define ABSTRACTENEMY_H

#include <QObject>
#include <unordered_map>
#include "abstractentity.h"
#include "utils/RNG.h"
#include "categories/intents.h"
#include "items/enemyIntent.h"
#include "combat/play_info.h"


class abstractEnemy : public abstractEntity
{
    Q_OBJECT

protected:

    std::unordered_map<int, enemy_intent> intent_list;
    int current_move;
    int enemy_turn = 0;

public:
    virtual void choose_move() = 0;
    virtual void play_turn(playInfo&) = 0;

    int get_current_move() { return current_move; }
    int get_enemy_turn() { return enemy_turn; }

    void perform_attack(playInfo&);
    void perform_block(playInfo&, int);

    abstractEnemy(QString name_init, int base_max_hp_init);
};

#endif // ABSTRACTENEMY_H
