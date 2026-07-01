#ifndef SPHERIC_GUARDIAN_H
#define SPHERIC_GUARDIAN_H

#include "abstractenemy.h"

enum class spheric_guardian_move {
    activate = 0,
    debuff_attack = 1,
    slam = 2,
    harden = 3
};


class spheric_guardian : public abstractEnemy
{
    Q_OBJECT

    spheric_guardian(QString name_init, int base_max_hp_init);

public:
    static spheric_guardian* create();
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::spheric_guardian ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // SPHERIC_GUARDIAN_H
