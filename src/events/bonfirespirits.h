#ifndef BONFIRESPIRITS_H
#define BONFIRESPIRITS_H

#include <QObject>

#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class BonfireSpirits : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    BonfireSpirits(game_action& actions, ironclad* player);

    const UnknownManager getManager() const { return manager; }
};

#endif // BONFIRESPIRITS_H
