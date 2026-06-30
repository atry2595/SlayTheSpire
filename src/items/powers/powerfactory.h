#ifndef POWERFACTORY_H
#define POWERFACTORY_H

#include <QWidget>
#include "abstractpower.h"
#include "dexteritypower.h"
#include "frailPower.h"
#include "metallicizePower.h"
#include "ritualpower.h"
#include "strengthpower.h"
#include "vulnerablePower.h"
#include "weakpower.h"

#include "categories/powers.h"

class powerFactory
{
    Q_OBJECT
public:
    static abstractPower* createPower(powerID id, abstractEntity* owner, int amount);
};

#endif // POWERFACTORY_H
