#ifndef RED_SLAVER_H
#define RED_SLAVER_H

#include "abstractenemy.h"

enum class red_slaver_move {
    stab = 0,
    scrape = 1,
    entangle = 2
};


class red_slaver : public abstractEnemy
{
    Q_OBJECT

    red_slaver(QString name_init, int base_max_hp_init);
    bool entangle_used = false;
public:
    static red_slaver* create(game_action& actions);
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::red_slaver ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
    QString get_story() override;
};

#endif // RED_SLAVER_H
