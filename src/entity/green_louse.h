#ifndef GREEN_LOUSE_H
#define GREEN_LOUSE_H

#include "abstractenemy.h"

enum class green_louse_move {
    bite = 0,
    spit_web = 1
};


class green_louse : public abstractEnemy
{
    Q_OBJECT

    green_louse(QString name_init, int base_max_hp_init);

public:
    static green_louse* create(game_action& actions);
    entityType get_type() override { return entityType::monster; }
    entityID get_ID() override { return entityID::green_louse ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
    QString get_story() override;
};

#endif // GREEN_LOUSE_H
