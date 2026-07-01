#ifndef RED_LOUSE_H
#define RED_LOUSE_H

#include "abstractenemy.h"

enum class red_louse_move {
    bite = 0,
    grow = 1
};


class red_louse : public abstractEnemy
{
    Q_OBJECT

    red_louse(QString name_init, int base_max_hp_init);

public:
    static red_louse* create();
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::red_louse ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // RED_LOUSE_H
