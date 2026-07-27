#include "infobarparent.h"
#include <QTimer>

infobarParent::infobarParent(QGraphicsItem* parent, barAlign al , QSizeF home_size)
    :BaseItem(parent, home_size, QPointF(home_size.width() * (2 * (al == barAlign::right) - 1), 0))
    ,align(al)
{
}

void infobarParent::Entrance() {
    moveTo({0, 0}, 500, QEasingCurve::OutBack);
}

void infobarParent::Exit() {
    moveTo(QPointF(home_size.width() * (2 * (align == barAlign::right) - 1), 0), 500, QEasingCurve::InBack);
}

void infobarParent::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    Exit();
    BaseItem::mousePressEvent(event);
    QTimer::singleShot(1000, [this](){deleteLater();});
}