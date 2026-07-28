#ifndef MAPITEMS_H
#define MAPITEMS_H

#include "map/map.h"
#include <QPointF>

struct RoomItem {
    Room source;
    qreal x;
    qreal y;
};

struct LineItem {
    QPointF origin;
    QPointF target;
};

#endif // MAPITEMS_H
