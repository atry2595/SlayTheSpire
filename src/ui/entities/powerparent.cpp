#include "powerparent.h"

PowerParent::PowerParent(combatEvent* event,
                           abstractPower* ent,
                           QGraphicsItem *parent,
                           QSizeF home_size,
                           QPointF home_pos)
    :BaseItem(parent, home_size, home_pos)
    ,eve(event)
    ,source(ent)
{
    setAcceptedMouseButtons(Qt::RightButton);
}

void PowerParent::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (event->button() == Qt::RightButton){
        emit eve->powerRightButton(source);
    }
}