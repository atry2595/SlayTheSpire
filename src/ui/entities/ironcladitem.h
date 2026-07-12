#ifndef IRONCLADITEM_H
#define IRONCLADITEM_H

#include "abstractentityitem.h"

class IroncladItem : public abstractEntityItem
{
    Q_OBJECT
    constexpr static int width = 214;
    constexpr static int height = 300;
public:
    IroncladItem(abstractEntity* source, QPointF pos, qreal zValue);

    void updateEntity();
};

#endif // IRONCLADITEM_H
