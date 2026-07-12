#include "entityparent.h"

EntityParent::EntityParent(QGraphicsItem *parent,
                           QSizeF home_size,
                           QPointF home_pos)
    :BaseItem(parent, home_size, home_pos)
{
}
