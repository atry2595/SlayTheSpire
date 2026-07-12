#ifndef IRONCLADITEM_H
#define IRONCLADITEM_H

#include "abstractentityitem.h"

class IroncladItem : public abstractEntityItem
{
    Q_OBJECT
public:
    IroncladItem(abstractEntity* source, QPointF pos, qreal zValue);

    void updateEntity();
};

#endif // IRONCLADITEM_H
