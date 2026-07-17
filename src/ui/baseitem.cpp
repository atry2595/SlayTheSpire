#include "baseitem.h"

#include <QPainter>
#include <QParallelAnimationGroup>
#include <QParallelAnimationGroup>

BaseItem::BaseItem(QGraphicsItem *parent,
                   QSizeF home_size,
                   QPointF home_pos)
    : QGraphicsObject(parent),
    home_pos(home_pos),
    home_size(home_size)
{
    m_size = home_size;

    this->home_size = home_size;

    this->home_pos = home_pos;

    setPos(home_pos);

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}


QRectF BaseItem::boundingRect() const
{
    return QRectF(0, 0, m_size.width(), m_size.height());
}

void BaseItem::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *,
                     QWidget *)
{
    if (has_bg){
        painter->setPen(Qt::NoPen);
        painter->setBrush(bg_col);
        painter->drawRect(boundingRect());
    }
}

void BaseItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mousePressEvent(event);

}

void BaseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsObject::mouseReleaseEvent(event);
}

void BaseItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsObject::hoverEnterEvent(event);
}

void BaseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsObject::hoverLeaveEvent(event);

}

// ---------- Home state ----------
void BaseItem::saveHomeState() {
    home_pos = pos();
    home_size = m_size;
    home_rotation = rotation();
    home_scale = scale();
    home_opacity = opacity();
    home_z = zValue();
}

// =========================
// Animation Factory
// =========================

QPropertyAnimation* BaseItem::createMoveAnimation(QPointF target,
                                                  int duration,
                                                  QEasingCurve easing)
{
    auto* anim = new QPropertyAnimation(this, "pos");
    anim->setDuration(duration);
    anim->setEndValue(target);
    anim->setEasingCurve(easing);
    return anim;
}

QPropertyAnimation* BaseItem::createRotateAnimation(qreal target,
                                                    int duration,
                                                    QEasingCurve easing)
{
    auto* anim = new QPropertyAnimation(this, "rotation");
    anim->setDuration(duration);
    anim->setStartValue(rotation());
    anim->setEndValue(target);
    anim->setEasingCurve(easing);
    return anim;
}

QPropertyAnimation* BaseItem::createScaleAnimation(qreal target,
                                                   int duration,
                                                   QEasingCurve easing)
{
    auto* anim = new QPropertyAnimation(this, "scale");
    anim->setDuration(duration);
    anim->setStartValue(scale());
    anim->setEndValue(target);
    anim->setEasingCurve(easing);
    return anim;
}

QPropertyAnimation* BaseItem::createOpacityAnimation(qreal target,
                                                     int duration,
                                                     QEasingCurve easing)
{
    auto* anim = new QPropertyAnimation(this, "opacity");
    anim->setDuration(duration);
    anim->setEndValue(target);
    anim->setEasingCurve(easing);
    return anim;
}

QPropertyAnimation* BaseItem::createResizeAnimation(QSizeF target,
                                                    int duration,
                                                    QEasingCurve easing)
{
    auto* anim = new QPropertyAnimation(this, "size");
    anim->setDuration(duration);
    anim->setEndValue(target);
    anim->setEasingCurve(easing);
    return anim;
}

QPropertyAnimation* BaseItem::createGeometryAnimation(QRectF target,
                                                      int duration,
                                                      QEasingCurve easing)
{
    auto* anim = new QPropertyAnimation(this, "geometry");
    anim->setDuration(duration);
    anim->setEndValue(target);
    anim->setEasingCurve(easing);
    return anim;
}

// =========================
// Quick Animation
// =========================

void BaseItem::moveTo(QPointF target,
                      int duration,
                      QEasingCurve easing)
{
    auto* anim = createMoveAnimation(target, duration, easing);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void BaseItem::rotateTo(qreal target,
                        int duration,
                        QEasingCurve easing)
{
    auto* anim = createRotateAnimation(target, duration, easing);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void BaseItem::scaleTo(qreal target,
                       int duration,
                       QEasingCurve easing)
{
    auto* anim = createScaleAnimation(target, duration, easing);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void BaseItem::fadeTo(qreal target,
                      int duration,
                      QEasingCurve easing)
{
    auto* anim = createOpacityAnimation(target, duration, easing);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void BaseItem::resizeTo(QSizeF target,
                        int duration,
                        QEasingCurve easing)
{
    auto* anim = createResizeAnimation(target, duration, easing);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void BaseItem::geometryTo(QRectF target,
                          int duration,
                          QEasingCurve easing)
{
    auto* anim = createGeometryAnimation(target, duration, easing);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}


void BaseItem::setSize(QSizeF size) {
    if (m_size == size)
        return;

    prepareGeometryChange();

    m_size = size;

    update();
}


void BaseItem::returnToHome(int duration)
{
    auto* group = new QParallelAnimationGroup(this);

    group->addAnimation(createMoveAnimation(home_pos, duration));
    group->addAnimation(createRotateAnimation(home_rotation, duration));
    group->addAnimation(createScaleAnimation(home_scale, duration));
    group->addAnimation(createOpacityAnimation(home_opacity, duration));
    group->addAnimation(createResizeAnimation(home_size, duration));

    group->start(QAbstractAnimation::DeleteWhenStopped);
}