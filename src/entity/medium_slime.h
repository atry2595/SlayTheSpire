#ifndef MEDIUM_SLIME_H
#define MEDIUM_SLIME_H

#include "abstractenemy.h"

enum class medium_slime_move {
    lick = 0,
    tackle = 1,
    corrosive_spit = 2
};


class medium_slime : public abstractEnemy
{
    Q_OBJECT

    medium_slime(QString name_init, int base_max_hp_init);

public:
    static medium_slime* create(game_action& actions, int hp_init = -1);
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::medium_slime ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // MEDIUM_SLIME_H
