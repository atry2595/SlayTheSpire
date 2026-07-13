#ifndef SHININGLIGHT_H
#define SHININGLIGHT_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class ShiningLight
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    ShiningLight(game_action&, ironclad*);

    const UnknownManager getManager() const
    {
        return manager;
    }
};

#endif // SHININGLIGHT_H