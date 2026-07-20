#include "potionparent.h"

PotionParent::PotionParent(combatEvent* eve,
                           abstractPotion* source,
                           QGraphicsItem *parent,
                           QSizeF home_size,
                           QPointF home_pos,
                           qreal z)
    :BaseItem(parent, home_size, home_pos),
    source(source),
    event(eve),
    hover_z(z)
{
    setAcceptedMouseButtons(Qt::RightButton | Qt::LeftButton);

    if (can_hover || can_select) {
        setFlag(QGraphicsItem::ItemIsMovable, true);
    }
    else {
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    if (can_select) {
        setFlag(QGraphicsItem::ItemIsSelectable, true);
    }
    else {
        setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
    moveAnim = createMoveAnimation(pos(), 150, final_easing);
    scaleAnim = createScaleAnimation(1.0, 150, final_easing);

    animGroup = new QParallelAnimationGroup(this);
    animGroup->addAnimation(moveAnim);
    animGroup->addAnimation(scaleAnim);
}


//-----------------------------------------------------------------

void PotionParent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);
    if (can_select && can_hover){
        refreshTargetPos();
        hoverEnterEvent(nullptr);
        emit this->event->potionPressed(this);
    }
    if (event->button() == Qt::RightButton){
        emit PotionParent::event->potionRightButton(source);
    }

}

//-----------------------------------------------------------------

void PotionParent::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {

    if (can_select) {
        QPointF scene = event->scenePos();
        emit this->event->potionMoved(this, scene);
    }
    QGraphicsObject::mouseMoveEvent(event);
}

//-----------------------------------------------------------------

void PotionParent::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (can_select) {
        QPointF scene = event->scenePos();
        refreshTargetPos();
        hoverLeaveEvent(nullptr);
        emit this->event->potionReleased(this, scene);
    }
    QGraphicsObject::mouseReleaseEvent(event);
}

//-----------------------------------------------------------------

void PotionParent::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (can_hover && !hovered) {
        hovered = true;
        final_easing = hover_enter_easing;
        refreshTargetPos();
        setZValue(zValue() + hover_z);
    }
    QGraphicsObject::hoverEnterEvent(event);
}

//-----------------------------------------------------------------

void PotionParent::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (can_hover && hovered) {
        hovered = false;
        final_easing = hover_leave_easing;
        refreshTargetPos();
        setZValue(zValue() - hover_z);
    }
    QGraphicsObject::hoverLeaveEvent(event);
}

//-----------------------------------------------------------------

void PotionParent::refreshTargetPos() {
    qreal h = homeSize().height();
    qreal w = homeSize().width();
    qreal n = 1; //sclae of card

    if (hovered) {
        n = hover_scale;
    }


    qreal x = homePos().x() - (w * (n-1) / 2);
    qreal y = homePos().y() - (h * (n-1) / 2);

    if (x != pos().x() || y != pos().y()) {
        updateVisualState(QPointF(x, y));
    }

}

//-----------------------------------------------------------------

void PotionParent::updateVisualState(QPointF targetPos)
{
    int time = hovered ? hover_time : 150;
    qreal scl = hovered ? hover_scale : 1.0;

    animGroup->stop();

    moveAnim->setStartValue(pos());
    moveAnim->setEndValue(targetPos);
    moveAnim->setDuration(time);

    scaleAnim->setStartValue(scale());
    scaleAnim->setEndValue(scl);
    scaleAnim->setDuration(time);

    animGroup->start();

}

//-----------------------------------------------------------------

void PotionParent::setCanHover(bool value) {
    can_hover = value;


    if (can_hover || can_select) {
        setFlag(QGraphicsItem::ItemIsMovable, true);
    }
    else {
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    if (can_select) {
        setFlag(QGraphicsItem::ItemIsSelectable, true);
    }
    else {
        setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}


void PotionParent::setCanSelect(bool value) {
    can_select = value;


    if (can_hover || can_select) {
        setFlag(QGraphicsItem::ItemIsMovable, true);
    }
    else {
        setFlag(QGraphicsItem::ItemIsMovable, false);
    }

    if (can_select) {
        setFlag(QGraphicsItem::ItemIsSelectable, true);
    }
    else {
        setFlag(QGraphicsItem::ItemIsSelectable, false);
    }
}

//-------------------------------------------------------------------------
void PotionParent::setHomePos(QPointF h) {
    BaseItem::setHomePos(h);
    refreshTargetPos();
}
