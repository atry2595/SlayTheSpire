#ifndef FACETRADER_H
#define FACETRADER_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class FaceTrader : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    FaceTrader(game_action&, ironclad*);

    const UnknownManager getManager() const { return manager; }
};

#endif // FACETRADER_H