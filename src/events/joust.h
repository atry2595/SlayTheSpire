#ifndef JOUST_H
#define JOUST_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class Joust : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    Joust(game_action& actions, ironclad* player);

    const UnknownManager getManager() const { return manager; }
};

#endif // JOUST_H
