#ifndef UNKNOWNFACTORY_H
#define UNKNOWNFACTORY_H

#include <QObject>
#include "UnknownMap.h"
#include "entity/ironclad.h"

class unknownFactory : public QObject
{
    Q_OBJECT
public:
    static UnknownManager createUnknown(unknownID id, game_action& actions, ironclad* player);
};

#endif // UNKNOWNFACTORY_H