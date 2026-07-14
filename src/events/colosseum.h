#ifndef COLOSSEUM_H
#define COLOSSEUM_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class Colosseum : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    Colosseum(game_action& actions, ironclad* player);

    const UnknownManager getManager() const { return manager; }
};

#endif // COLOSSEUM_H
