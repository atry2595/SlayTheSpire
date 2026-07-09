#include "cardparent.h"
#include <QParallelAnimationGroup>

CardParent::CardParent(QGraphicsItem *parent,
                       QSizeF home_size,
                       QPointF home_pos)
    :BaseItem(parent, home_size, home_pos)
{
    animGroup = new QSequentialAnimationGroup();
}


void CardParent::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (can_select) {
        selected = !selected;
        if (selected) final_easing = selected_enter_easing;
        else final_easing = selected_leave_easing;
        refreshTargetPos();
    }
    QGraphicsObject::mousePressEvent(event);
}


void CardParent::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if (can_hover) {
        hovered = true;
        final_easing = hover_enter_easing;
        refreshTargetPos();
    }
    QGraphicsObject::hoverEnterEvent(event);
}

void CardParent::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    if (can_hover) {
        hovered = false;
        final_easing = hover_leave_easing;
        refreshTargetPos();
    }
    QGraphicsObject::hoverLeaveEvent(event);
}


void CardParent::refreshTargetPos() {
    qreal h = homeSize().height();
    qreal w = homeSize().width();
    qreal n = 1; //sclae of card
    qreal k = 0; //vert offset of card

    if (selected){
        n = selected_scale;
        k = selected_offset;
    }
    else if (hovered) {
        n = hover_scale;
        k = hover_offset;
    }


    qreal x = homePos().x() - (w * (n-1) / 2);
    qreal y = homePos().y() - (h * (n-1) / 2) + (k * n);

    if (x != pos().x() || y != pos().y()) {
        updateVisualState(QPointF(x, y));
    }
}


void CardParent::updateVisualState(QPointF targetPos){
    animGroup->stop();

    while(animGroup->animationCount())
    {
        delete animGroup->animationAt(0);
    }

    int time = 150;
    qreal scl = 1;

    if (selected) {
        time = selected_time;
        scl = selected_scale;
    }
    else if (hovered) {
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