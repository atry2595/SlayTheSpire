#ifndef OMINOUSFORGE_H
#define OMINOUSFORGE_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class OminousForge
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    OminousForge(game_action&, ironclad*);

    const UnknownManager getManager() const { return manager; }
};

#endif // OMINOUSFORGE_H
