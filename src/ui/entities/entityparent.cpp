#include "entityparent.h"

EntityParent::EntityParent(combatEvent* event,
                           abstractEntity* ent,
                           QGraphicsItem *parent,
                           QSizeF home_size,
                           QPointF home_pos)
    :BaseItem(parent, home_size, home_pos)
    ,eve(event)
    ,source(ent)
{
    setAcceptedMouseButtons(Qt::RightButton);
}

void EntityParent::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::RightButton){
        emit eve->entityRightButton(source);
    }
}