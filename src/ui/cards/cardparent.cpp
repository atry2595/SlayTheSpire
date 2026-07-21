#include "cardparent.h"


CardParent::CardParent(combatEvent* eve,
                       QGraphicsItem *parent,
                       QSizeF home_size,
                       QPointF home_pos,
                       qreal z)
    :BaseItem(parent, home_size, home_pos),
    event(eve),
    hover_z(z)
{
    setAcceptedMouseButtons(Qt::LeftButton);

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

void CardParent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (can_select && can_hover){
        refreshTargetPos();
        hoverEnterEvent(nullptr);
    }
    emit this->event->cardPressed(this);
    QGraphicsObject::mousePressEvent(event);

}

//-----------------------------------------------------------------

void CardParent::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {

    if (can_select) {
        QPointF scene = event->scenePos();
        emit this->event->cardMoved(this, scene);
    }
    QGraphicsObject::mouseMoveEvent(event);
}

//-----------------------------------------------------------------

void CardParent::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (can_select) {
        QPointF scene = event->scenePos();
        refreshTargetPos();
        hoverLeaveEvent(nullptr);
        emit this->event->cardReleased(this, scene);
    }
    QGraphicsObject::mouseReleaseEvent(event);
}

//-----------------------------------------------------------------

void CardParent::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
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

void CardParent::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
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

void CardParent::refreshTargetPos() {
    qreal h = homeSize().height();
    qreal w = homeSize().width();
    qreal n = 1; //sclae of card
    qreal k = 0; //vert offset of card

    if (hovered) {
        n = hover_scale;
        k = hover_offset;
    }


    qreal x = homePos().x() - (w * (n-1) / 2);
    qreal y = homePos().y() - (h * (n-1) / 2) + (k * n);

    if (x != pos().x() || y != pos().y()) {
        updateVisualState(QPointF(x, y));
    }

}

//-----------------------------------------------------------------

// void CardParent::updateVisualState(QPointF targetPos){
//     animGroup->stop();

//     while(animGroup->animationCount())
//     {
//         delete animGroup->animationAt(0);
//     }

//     int time = 150;
//     qreal scl = 1;

//     if (hovered) {
//         time = hover_time;
//         scl = hover_scale;
//     }

//     auto* anim = new QParallelAnimationGroup(animGroup);
//     anim->addAnimation(this->createScaleAnimation(scl, time, final_easing));
//     anim->addAnimation(this->createMoveAnimation(targetPos, time, final_easing));
//     animGroup->addAnimation(anim);

//     animGroup->setCurrentTime(0);
//     animGroup->start();

// }

void CardParent::updateVisualState(QPointF targetPos)
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

void CardParent::setCanHover(bool value) {
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


void CardParent::setCanSelect(bool value) {
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
void CardParent::setHomePos(QPointF h) {
    BaseItem::setHomePos(h);
    refreshTargetPos();
}
