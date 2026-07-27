#ifndef SMALL_SLIME_H
#define SMALL_SLIME_H

#include "abstractenemy.h"

enum class small_slime_move {
    lick = 0,
    tackle = 1
};


class small_slime : public abstractEnemy
{
    Q_OBJECT

    small_slime(QString name_init, int base_max_hp_init);

public:
    static small_slime* create(game_action& actions);
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::small_slime ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
    QString get_story() override;
};

#endif // SMALL_SLIME_H
