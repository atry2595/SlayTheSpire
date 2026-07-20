#include "relicparent.h"

RelicParent::RelicParent(combatEvent* event,
                           abstractRelic* ent,
                           QGraphicsItem *parent,
                           QSizeF home_size,
                           QPointF home_pos)
    :BaseItem(parent, home_size, home_pos)
    ,eve(event)
    ,source(ent)
{
    setAcceptedMouseButtons(Qt::RightButton);
}

void RelicParent::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::RightButton){
        emit eve->relicRightButton(source);
    }
}