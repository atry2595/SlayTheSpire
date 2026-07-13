#ifndef TASKMASTERITEM_H
#define TASKMASTERITEM_H

#include "abstractentityitem.h"

class TaskmasterItem : public abstractEntityItem
{
    Q_OBJECT
    constexpr static int width = 212;
    constexpr static int height = 250;
public:
    TaskmasterItem(abstractEntity* source, QPointF pos, qreal zValue);

    void updateEntity();
};

#endif // TASKMASTERITEM_H
