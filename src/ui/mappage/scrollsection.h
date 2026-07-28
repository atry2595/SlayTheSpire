#ifndef SCROLLSECTION_H
#define SCROLLSECTION_H

#include "ui/baseitem.h"
#include <QGraphicsSceneWheelEvent>

class ScrollSection : public BaseItem
{
    Q_OBJECT
    bool hovered = true;
    qreal y_offset = 0;
    qreal max_offset = -1;
    qreal min_offset = 0;

    QPropertyAnimation* anim;

    void updateVisualState();

protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent*) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent*) override;
    void wheelEvent(QGraphicsSceneWheelEvent*) override;
public:
    ScrollSection(QGraphicsItem* parent = nullptr, QSizeF home_size = {0, 0}, QPointF home_pos = {0, 0},
                  qreal offset = 0, qreal max_ofsset = -1, qreal min_offset = 0);

    void setOffset(qreal value) { y_offset = std::max(min_offset, std::min(max_offset, value)); }
    void setMaxOffset(qreal value) { max_offset = (max_offset != -1) ? (value) : (size().height()); }
    void setMinOffset(qreal value) { min_offset = value; }

    qreal getOffset() { return y_offset; }
    qreal getMaxOffset() { return max_offset; }
    qreal getMinOffset() { return min_offset; }
    bool getHovered() { return hovered; }
};

#endif // SCROLLSECTION_H
