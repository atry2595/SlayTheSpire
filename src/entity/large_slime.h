#ifndef LARGE_SLIME_H
#define LARGE_SLIME_H

#include "abstractenemy.h"

enum class large_slime_move {
    lick = 0,
    tackle = 1,
    corrosive_spit = 2,
    split = 3
};


class large_slime : public abstractEnemy
{
    Q_OBJECT
    QMetaObject::Connection half_hp_connection;
    large_slime(QString name_init, int base_max_hp_init);

public:
    static large_slime* create(game_action& actions, int hp_init = -1);
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::large_slime ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
    QString get_story() override;
};

#endif // LARGE_SLIME_H
