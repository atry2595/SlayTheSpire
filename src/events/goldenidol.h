#ifndef GOLDENIDOL_H
#define GOLDENIDOL_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class GoldenIdol
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    GoldenIdol(game_action&, ironclad*);

    const UnknownManager getManager() const { return manager; }
};

#endif // GOLDENIDOL_H