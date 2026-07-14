#ifndef PLEADINGVAGRANT_H
#define PLEADINGVAGRANT_H

#include <QObject>

#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class PleadingVagrant  : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    PleadingVagrant(game_action&, ironclad*);

    const UnknownManager getManager() const
    {
        return manager;
    }
};

#endif // PLEADINGVAGRANT_H