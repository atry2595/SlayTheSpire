#ifndef ENEMYINTENT_H
#define ENEMYINTENT_H

#include <QString>
#include "categories/intents.h"

struct enemy_intent{

    QString name;
    intent_type type;
    int damage = 0;
    int repeat = 1;

};

#endif // ENEMYINTENT_H
