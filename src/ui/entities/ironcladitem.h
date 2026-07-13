#ifndef IRONCLADITEM_H
#define IRONCLADITEM_H

#include "abstractentityitem.h"

class IroncladItem : public abstractEntityItem
{
    Q_OBJECT
    constexpr static int width = 300;
    constexpr static int height = 214;
public:
    IroncladItem(abstractEntity* source, QPointF pos, qreal zValue);

    void updateEntity();
};

#endif // IRONCLADITEM_H
