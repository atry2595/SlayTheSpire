#ifndef POWERFACTORY_H
#define POWERFACTORY_H

#include <QWidget>
#include "abstractpower.h"


#include "categories/powers.h"

class PowerFactory : public QObject
{
    Q_OBJECT
public:
    static abstractPower* createPower(powerID id, abstractEntity* owner, int amount);
};

#endif // POWERFACTORY_H
