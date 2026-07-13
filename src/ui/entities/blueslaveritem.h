#ifndef BLUSLAVERITEM_H
#define BLUSLAVERITEM_H

#include "abstractentityitem.h"

class BlueSlaverItem : public abstractEntityItem
{
    Q_OBJECT
    constexpr static int width = 254;
    constexpr static int height = 214;
public:
    BlueSlaverItem(abstractEntity* source, QPointF pos, qreal zValue);

    void updateEntity();
};

#endif // BLUSLAVERITEM_H
