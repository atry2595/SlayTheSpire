#ifndef SLIME_BOSS_H
#define SLIME_BOSS_H

#include "abstractenemy.h"

enum class slime_boss_move {
    goop_spray = 0,
    preparing = 1,
    slam = 2,
    split = 3
};


class slime_boss : public abstractEnemy
{
    Q_OBJECT
    QMetaObject::Connection half_hp_connection;
    slime_boss(QString name_init, int base_max_hp_init);

public:
    static slime_boss* create(game_action& actions);
    entityType get_type() override { return entityType::boss; }
    entityID get_ID() override { return entityID::slime_boss ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
    QString get_story() override;
};

#endif // SLIME_BOSS_H
