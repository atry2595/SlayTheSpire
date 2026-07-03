#ifndef ABSTRACTENEMY_H
#define ABSTRACTENEMY_H

#include <QObject>
#include "abstractentity.h"

class abstractIntent;
typedef enum {monster, elite, boss}enemyType;

class abstractEnemy : public abstractEntity
{
    Q_OBJECT

protected:
    enemyType type;

    std::vector<abstractIntent*> intent_list;
    abstractIntent* current_intent;

public:
    virtual void choose_intent(int turn) = 0;
    virtual void play_turn() = 0;

    abstractEnemy(QString name_init, int base_max_hp_init);
};

#endif // ABSTRACTENEMY_H
