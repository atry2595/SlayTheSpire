#ifndef GOLDENSHRINE_H
#define GOLDENSHRINE_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class GoldenShrine : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    GoldenShrine(game_action&, ironclad*);

    const UnknownManager getManager() const { return manager; }
};

#endif // GOLDENSHRINE_H