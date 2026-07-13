#ifndef REDSLAVERITEM_H
#define REDSLAVERITEM_H

#include "abstractentityitem.h"

class RedSlaverItem : public abstractEntityItem
{
    Q_OBJECT
    constexpr static int width = 264;
    constexpr static int height = 214;
public:
    RedSlaverItem(abstractEntity* source, QPointF pos, qreal zValue);

    void updateEntity();
};

#endif // REDSLAVERITEM_H
