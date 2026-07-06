#ifndef SENTRY_H
#define SENTRY_H

#include "abstractenemy.h"

enum class sentry_move {
    bolt = 0,
    beam= 1
};


class sentry : public abstractEnemy
{
    Q_OBJECT

    sentry(QString name_init, int base_max_hp_init);
public:
    static sentry* create(game_action& actions, bool is_middle = false);
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::sentry;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // SENTRY_H
