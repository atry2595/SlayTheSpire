#ifndef CULTIST_H
#define CULTIST_H

#include "abstractenemy.h"

enum class cultist_move {
    incantation = 0,
    dark_strike = 1
};


class cultist : public abstractEnemy
{
    Q_OBJECT

    cultist(QString name_init, int base_max_hp_init);

public:
    static cultist* create();
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::cultist ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // CULTIST_H
