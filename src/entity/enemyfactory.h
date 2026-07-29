#ifndef ENEMYFACTORY_H
#define ENEMYFACTORY_H

#include <QObject>
#include "abstractenemy.h"
#include "categories/enemies.h"

class enemyFactory : public QObject
{
    Q_OBJECT
public:
    static abstractEnemy* createEnemy(entityID id, game_action& actions, bool middle = false);
};

#endif // ENEMYFACTORY_H