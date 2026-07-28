#include "scrollsection.h"

ScrollSection::ScrollSection(QGraphicsItem* parent , QSizeF home_size ,
            QPointF home_pos , qreal offset , qreal max_ofsset , qreal min_offset)
    :BaseItem(parent, home_size, home_pos)
    ,y_offset(offset)
    ,max_offset(max_ofsset)
    ,min_offset(min_offset)
{
    setAcceptHoverEvents(true);
    setPos(QPointF(home_pos.x(), -offset));
    anim = createMoveAnimation(QPointF(home_pos.x(), -offset), 150, QEasingCurve::OutSine);
    anim->start();
}


void ScrollSection::hoverEnterEvent(QGraphicsSceneHoverEvent* event) {
    hovered = true;
    BaseItem::hoverEnterEvent(event);
}

void ScrollSection::hoverLeaveEvent(QGraphicsSceneHoverEvent* event) {
    hovered = false;
    BaseItem::hoverLeaveEvent(event);
}

void ScrollSection::wheelEvent(QGraphicsSceneWheelEvent* event) {
    if (hovered) {
        qreal value = event->delta() / 2.5;
        y_offset = std::max(min_offset, std::min(y_offset - value, max_offset));
        updateVisualState();
    }
    BaseItem::wheelEvent(event);
}

void ScrollSection::updateVisualState() {
    if (anim->state() == QAbstractAnimation::Running) {
        anim->stop();
    }
    anim->setStartValue(anim->currentValue());
    anim->setEndValue(QPointF(pos().x(), -y_offset));
    anim->start();
}