#ifndef BLUE_SLAVER_H
#define BLUE_SLAVER_H

#include "abstractenemy.h"

enum class blue_slaver_move {
    stab = 0,
    rake = 1
};


class blue_slaver : public abstractEnemy
{
    Q_OBJECT

    blue_slaver(QString name_init, int base_max_hp_init);

public:
    static blue_slaver* create();
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::blue_slaver ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // BLUE_SLAVER_H
