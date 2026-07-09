#ifndef CARDPARENT_H
#define CARDPARENT_H

#include "ui/baseitem.h"
#include <QSequentialAnimationGroup>

class CardParent : public BaseItem
{
    Q_OBJECT

private:
    // State
    bool can_hover = true;
    bool can_select = true;

    bool hovered = false;
    bool selected = false;

    // Hover
    qreal hover_scale = 1.5;
    qreal hover_offset = -100.0;

    int hover_time = 100;

    QEasingCurve::Type hover_enter_easing = QEasingCurve::OutSine;
    QEasingCurve::Type hover_leave_easing = QEasingCurve::InSine;

    // Selected
    qreal selected_scale = 1.5;
    qreal selected_offset = -100.0;

    int selected_time = 100;

    QEasingCurve::Type selected_enter_easing = QEasingCurve::OutSine;
    QEasingCurve::Type selected_leave_easing = QEasingCurve::InSine;

    QEasingCurve::Type final_easing = QEasingCurve::Linear;

    void updateVisualState(QPointF targetPos);

    QSequentialAnimationGroup* animGroup = nullptr;

    qreal z_value;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;

    void refreshTargetPos();

public:
    explicit CardParent(QGraphicsItem* parent = nullptr,
                        QSizeF home_size = {0,0},
                        QPointF home_pos = {0,0},
                        qreal zValue = 0);

    // Hover Enable
    void setCanHover(bool value) { can_hover = value; }
    bool canHover() const { return can_hover; }

    // Select Enable
    void setCanSelect(bool value) { can_select = value; }
    bool canSelect() const { return can_select; }

    // Hovered
    void setHovered(bool value) { hovered = value; }
    bool isHovered() const { return hovered; }

    // Selected
    void setSelected(bool value) { selected = value; }
    bool isSelected() const { return selected; }

    // Hover Scale
    void setHoverScale(qreal value) { hover_scale = value; }
    qreal hoverScale() const { return hover_scale; }

    // Hover Offset
    void setHoverOffset(qreal value) { hover_offset = value; }
    qreal hoverOffset() const { return hover_offset; }

    // Hover Time
    void setHoverTime(int value) { hover_time = value; }
    int hoverTime() const { return hover_time; }

    // Hover Easing
    void setHoverEnterEasing(QEasingCurve::Type value) { hover_enter_easing = value; }
    QEasingCurve::Type hoverEnterEasing() const { return hover_enter_easing; }

    void setHoverLeaveEasing(QEasingCurve::Type value) { hover_leave_easing = value; }
    QEasingCurve::Type hoverLeaveEasing() const { return hover_leave_easing; }

    // Selected Scale
    void setSelectedScale(qreal value) { selected_scale = value; }
    qreal selectedScale() const { return selected_scale; }

    // Selected Offset
    void setSelectedOffset(qreal value) { selected_offset = value; }
    qreal selectedOffset() const { return selected_offset; }

    // Selected Time
    void setSelectedTime(int value) { selected_time = value; }
    int selectedTime() const { return selected_time; }

    // Selected Easing
    void setSelectedEnterEasing(QEasingCurve::Type value) { selected_enter_easing = value; }
    QEasingCurve::Type selectedEnterEasing() const { return selected_enter_easing; }

    void setSelectedLeaveEasing(QEasingCurve::Type value) { selected_leave_easing = value; }
    QEasingCurve::Type selectedLeaveEasing() const { return selected_leave_easing; }
};

#endif