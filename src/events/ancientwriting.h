#ifndef ANCIENTWRITING_H
#define ANCIENTWRITING_H

#include <QObject>

#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class AncientWriting : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    AncientWriting(game_action&, ironclad*);

    const UnknownManager getManager() const { return manager; }
};

#endif // ANCIENTWRITING_H