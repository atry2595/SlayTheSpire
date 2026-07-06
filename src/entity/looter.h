#ifndef LOOTER_H
#define LOOTER_H

#include "abstractenemy.h"

enum class looter_move {
    mug = 0,
    lunge = 1,
    smoke_bomb = 2,
    escape = 3
};


class looter : public abstractEnemy
{
    Q_OBJECT

    looter(QString name_init, int base_max_hp_init);

public:
    static looter* create(game_action& actions);
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::looter ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // LOOTER_H
