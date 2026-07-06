#ifndef MUGGER_H
#define MUGGER_H

#include "abstractenemy.h"

enum class mugger_move {
    mug = 0,
    lunge = 1,
    smoke_bomb = 2,
    escape = 3
};


class mugger : public abstractEnemy
{
    Q_OBJECT

    mugger(QString name_init, int base_max_hp_init);

public:
    static mugger* create(game_action& actions);
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::mugger ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // MUGGER_H
