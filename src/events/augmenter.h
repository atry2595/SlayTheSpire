#ifndef AUGMENTER_H
#define AUGMENTER_H

#include <QObject>
#include "events/UnknownMap.h"
#include "combat/game_action.h"
#include "entity/ironclad.h"

class Augmenter : public QObject
{
    Q_OBJECT

private:
    UnknownManager manager;

public:
    Augmenter(game_action&, ironclad*);

    const UnknownManager getManager() const
    {
        return manager;
    }
};

#endif // AUGMENTER_H