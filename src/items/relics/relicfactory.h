#ifndef RELICFACTORY_H
#define RELICFACTORY_H

#include <QObject>
#include "abstractrelic.h"


#include "categories/relics.h"

class RelicFactory : public QObject
{
    Q_OBJECT
public:
    static abstractRelic* createRelic(relicID id, abstractEntity* owner);
};
#endif // RELICFACTORY_H
