#ifndef HEXAGHOST_H
#define HEXAGHOST_H

#include "abstractenemy.h"

enum class hexaghost_move {
    activate = 0,
    divider = 1,
    sear = 2,
    tackle = 3,
    inflame = 4,
    inferno = 5
};


class hexaghost : public abstractEnemy
{
    Q_OBJECT

    hexaghost(QString name_init, int base_max_hp_init);
    bool upgrade_burn = false;

public:
    static hexaghost* create(game_action& actions);
    entityType get_type() override { return entityType::boss; }
    entityID get_ID() override { return entityID::hexaghost ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // HEXAGHOST_H
