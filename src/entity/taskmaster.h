#ifndef TASKMASTER_H
#define TASKMASTER_H

#include "abstractenemy.h"

enum class taskmaster_move {
    scouring_whip = 0
};


class taskmaster : public abstractEnemy
{
    Q_OBJECT

    taskmaster(QString name_init, int base_max_hp_init);

public:
    static taskmaster* create(game_action& actions);
    entityType get_type() override { return entityType::elite; }
    entityID get_ID() override { return entityID::taskmaster ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
    QString get_story() override;
};

#endif // TASKMASTER_H
