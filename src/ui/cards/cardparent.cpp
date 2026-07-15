#include "cardparent.h"
#include <QParallelAnimationGroup>


CardParent::CardParent(QGraphicsItem *parent,
                       QSizeF home_size,
                       QPointF home_pos,
                       qreal z)
    :BaseItem(parent, home_size, home_pos),
    hover_z(z)
{
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
    animGroup = new QSequentialAnimationGroup();
}

//-----------------------------------------------------------------

void CardParent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (can_select && can_hover && !hovered){
        refreshTargetPos();
        hoverEnterEvent(nullptr);
    }
    QGraphicsObject::mousePressEvent(event);
}

//-----------------------------------------------------------------

void CardParent::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (can_select) {
        refreshTargetPos();
        hoverLeaveEvent(nullptr);
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

void CardParent::updateVisualState(QPointF targetPos){
    animGroup->stop();

    while(animGroup->animationCount())
    {
        delete animGroup->animationAt(0);
    }

    int time = 150;
    qreal scl = 1;

    if (hovered) {
        time = hover_time;
        scl = hover_scale;
    }

    auto* anim = new QParallelAnimationGroup(animGroup);
    anim->addAnimation(this->createScaleAnimation(scl, time, final_easing));
    anim->addAnimation(this->createMoveAnimation(targetPos, time, final_easing));
    animGroup->addAnimation(anim);

    animGroup->setCurrentTime(0);
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
