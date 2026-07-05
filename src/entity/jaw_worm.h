#ifndef JAW_WORM_H
#define JAW_WORM_H

#include "abstractenemy.h"

enum class jaw_worm_move {
    chomp = 0,
    bellow = 1,
    thrash = 2
};


class jaw_worm : public abstractEnemy
{
    Q_OBJECT

    jaw_worm(QString name_init, int base_max_hp_init);

public:
    static jaw_worm* create(game_action& actions);
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::jaw_worm ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // JAW_WORM_H
