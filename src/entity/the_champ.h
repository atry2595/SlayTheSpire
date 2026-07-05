#ifndef THE_CHAMP_H
#define THE_CHAMP_H

#include "abstractenemy.h"

enum class the_champ_move {
    heavy_slash = 0,
    face_slap = 1,
    defensive_stance = 2,
    gloat = 3,
    taunt = 4,
    anger = 5,
    execute = 6
};


class the_champ : public abstractEnemy
{
    Q_OBJECT

    int phase = 1;
    int phase_turn = 0;

    the_champ(QString name_init, int base_max_hp_init);

public:
    static the_champ* create(game_action& actions);
    entityType get_type() override { return entityType::boss; }
    entityID get_ID() override { return entityID::the_champ ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // THE_CHAMP_H
