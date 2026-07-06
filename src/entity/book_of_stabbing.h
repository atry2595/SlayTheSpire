#ifndef BOOK_OF_STABBING_H
#define BOOK_OF_STABBING_H

#include "abstractenemy.h"

enum class book_of_stabbing_move {
    multi_stab = 0,
    big_stab = 1
};


class book_of_stabbing : public abstractEnemy
{
    Q_OBJECT

    book_of_stabbing(QString name_init, int base_max_hp_init);

public:
    static book_of_stabbing* create(game_action& actions);
    entityType get_type() override { return entityType::elite; }
    entityID get_ID() override { return entityID::book_of_stabbing ;}

    void choose_move() override;
    void play_turn(playInfo&)  override;
};

#endif // BOOK_OF_STABBING_H
