#ifndef LAB_H
#define LAB_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class Lab  : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    Lab(game_action&, ironclad*);

    const UnknownManager getManager() const { return manager; }
};

#endif // LAB_H