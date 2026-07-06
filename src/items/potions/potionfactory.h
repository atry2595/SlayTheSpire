#ifndef POTIONFACTORY_H
#define POTIONFACTORY_H

#include <QObject>
#include "abstractpotion.h"


#include "categories/powers.h"

class PotionFactory : public QObject
{
    Q_OBJECT
public:
    static abstractPotion* createPotion(potionID id, abstractEntity* owner);
};

#endif // POTIONFACTORY_H
