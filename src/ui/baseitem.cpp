#include "baseitem.h"

#include <QPainter>
#include <QDebug>

BaseItem::BaseItem(QGraphicsItem* parent)
    : QGraphicsObject(parent)
{
    moveAnim = new QPropertyAnimation(this, "pos");
    moveAnim->setDuration(80);
    setAcceptedMouseButtons(Qt::LeftButton);
    setAcceptHoverEvents(true);
    valed = !(parent == nullptr);
}

QRectF BaseItem::boundingRect() const {
    return QRectF(QPointF(0,0),itemSize);
}

void BaseItem::paint(QPainter* painter,
                     const QStyleOptionGraphicsItem* option,
                     QWidget* widget) {

    if (hasPixmap){
        painter->drawPixmap(boundingRect().toRect(), pixmap);
    }
    else {
        if (selected) painter->setBrush(Qt::magenta);
        else painter->setBrush(Qt::blue);
        painter->drawRect(boundingRect());
    }
}


void BaseItem::setSize(qreal width, qreal height) {
    prepareGeometryChange();
    itemSize = QSizeF(width, height);
}

void BaseItem::moveTo(QPointF point){
    if (valed) return;
    moveAnim->stop();

    moveAnim->setStartValue(pos());
    moveAnim->setEndValue(point);

    moveAnim->start();
}

void BaseItem::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    if (valed) return;
    qDebug() << "Presed";
    selected = !selected;
    QGraphicsObject::mousePressEvent(event);
    update();
}

void BaseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    if (valed) return;
    qDebug() << "Released"   ;
    QGraphicsObject::mouseReleaseEvent(event);
}


void BaseItem::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    if (valed) return;
    qDebug() << "yoooooooooo";
    moveTo(home + QPointF(0, -50));
    QGraphicsObject::hoverEnterEvent(event);
}

void BaseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    if (valed) return;
    qDebug() << "yeeeeeeeeeee";
    if (!selected) moveTo(home);
    QGraphicsObject::hoverLeaveEvent(event);
}
