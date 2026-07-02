#ifndef CARDFACTORY_H
#define CARDFACTORY_H

#include <QObject>
#include "abstractcard.h"

#include "categories/cards.h"

class CardFactory : public QObject
{
    Q_OBJECT
public:
    static abstractCard* createCard(cardID id);
};

#endif // CARDFACTORY_H
