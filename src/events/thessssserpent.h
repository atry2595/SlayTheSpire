#ifndef THESSSSSERPENT_H
#define THESSSSSERPENT_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class TheSsssserpent : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    TheSsssserpent(game_action& actions, ironclad* player);

    const UnknownManager getManager() const { return manager; }
};

#endif // THESSSSSERPENT_H
