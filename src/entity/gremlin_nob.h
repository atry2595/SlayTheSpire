#ifndef GREMLIN_NOB_H
#define GREMLIN_NOB_H

#include "abstractenemy.h"

enum class gremlin_nob_move {
    bellow = 0,
    skull_bash = 1,
    bull_rush = 2
};


class gremlin_nob : public abstractEnemy
{
    Q_OBJECT

    gremlin_nob(QString name_init, int base_max_hp_init);
public:
    static gremlin_nob* create(game_action& actions);
    entityType get_type() override { return entityType::elite; }
    entityID get_ID() override { return entityID::gremlin_nob ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // GREMLIN_NOB_H
