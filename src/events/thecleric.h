#ifndef THECLERIC_H
#define THECLERIC_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class TheCleric  : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    TheCleric(game_action&, ironclad*);

    const UnknownManager getManager() const
    {
        return manager;
    }
};

#endif // THECLERIC_H