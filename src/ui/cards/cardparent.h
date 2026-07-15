#ifndef CARDPARENT_H
#define CARDPARENT_H

#include "ui/baseitem.h"
#include <QSequentialAnimationGroup>

class CardParent : public BaseItem
{
    Q_OBJECT

private:
    //==========State==========
    bool can_hover = true;
    bool can_select = true;
    bool hovered = false;
    QEasingCurve::Type final_easing = QEasingCurve::Linear;
    //==========State==========


    //==========Hover==========
    qreal hover_scale = 1.5;
    qreal hover_offset = -100.0;
    int hover_time = 100;
    qreal hover_z = 100;
    QEasingCurve::Type hover_enter_easing = QEasingCurve::OutSine;
    QEasingCurve::Type hover_leave_easing = QEasingCurve::InSine;
    //==========Hover==========


    //==========update place & size==========
    void refreshTargetPos();
    void updateVisualState(QPointF targetPos);

    QSequentialAnimationGroup* animGroup = nullptr;
    //==========update place & size==========


protected:
    //==========mouse event=================
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    //==========mouse event=================


public:
    //==========constructor==============
    explicit CardParent(QGraphicsItem* parent = nullptr,
                        QSizeF home_size = {0,0},
                        QPointF home_pos = {0,0},
                        qreal z = 100);
    //==========constructor==============


    //=============getters===============
    bool getCanHover() const { return can_hover; }
    bool getCanSelect() const { return can_select; }
    bool getIsHovered() const { return hovered; }
    qreal getHoverScale() const { return hover_scale; }
    qreal getHoverOffset() const { return hover_offset; }
    int hoverTime() const { return hover_time; }
    qreal getHoverZ() const { return hover_z; }
    QEasingCurve::Type hoverEnterEasing() const { return hover_enter_easing; }
    QEasingCurve::Type hoverLeaveEasing() const { return hover_leave_easing; }
    //=============getters===============


    //=============setters===============
    void setCanHover(bool value);
    void setCanSelect(bool value);
    void setHovered(bool value) { hovered = value; }
    void setHoverScale(qreal value) { hover_scale = value; }
    void setHoverOffset(qreal value) { hover_offset = value; }
    void setHoverTime(int value) { hover_time = value; }
    void setHoverZ(qreal z) { hover_z = z; }
    void setHoverEnterEasing(QEasingCurve::Type value) { hover_enter_easing = value; }
    void setHoverLeaveEasing(QEasingCurve::Type value) { hover_leave_easing = value; }
    void setHomePos(QPointF) override;
    //=============setters===============

};

#endif