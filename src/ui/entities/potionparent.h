#ifndef POTIONPARENT_H
#define POTIONPARENT_H

#include "ui/baseitem.h"
#include "items/potions/abstractpotion.h"
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>
#include <QGraphicsSceneMouseEvent>

class PotionParent : public BaseItem
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
    qreal hover_scale = 1.2;
    int hover_time = 100;
    qreal hover_z = 400;
    QEasingCurve::Type hover_enter_easing = QEasingCurve::OutSine;
    QEasingCurve::Type hover_leave_easing = QEasingCurve::InSine;
    //==========Hover==========


    //==========update place & size==========
    void refreshTargetPos();
    void updateVisualState(QPointF targetPos);
    //==========update place & size==========

    //=============data========
    abstractPotion* source = nullptr;
    combatEvent* event;
    //=============data========

    //=============help========
    QPropertyAnimation* moveAnim;
    QPropertyAnimation* scaleAnim;
    QParallelAnimationGroup* animGroup;
    //=============help========


protected:
    //==========mouse event=================
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* event) override;
    //==========mouse event=================


public:
    //==========constructor==============
    explicit PotionParent(combatEvent* eve,
                        abstractPotion* source,
                        QGraphicsItem* parent = nullptr,
                        QSizeF home_size = {0,0},
                        QPointF home_pos = {0,0},
                        qreal z = 400);
    //==========constructor==============


    //=============getters===============
    bool getCanHover() const { return can_hover; }
    bool getCanSelect() const { return can_select; }
    bool getIsHovered() const { return hovered; }
    qreal getHoverScale() const { return hover_scale; }
    int hoverTime() const { return hover_time; }
    qreal getHoverZ() const { return hover_z; }
    QEasingCurve::Type hoverEnterEasing() const { return hover_enter_easing; }
    QEasingCurve::Type hoverLeaveEasing() const { return hover_leave_easing; }
    abstractPotion* getSource() { return source; }
    //=============getters===============


    //=============setters===============
    void setCanHover(bool value);
    void setCanSelect(bool value);
    void setHovered(bool value) { hovered = value; }
    void setHoverScale(qreal value) { hover_scale = value; }
    void setHoverTime(int value) { hover_time = value; }
    void setHoverZ(qreal z) { hover_z = z; }
    void setHoverEnterEasing(QEasingCurve::Type value) { hover_enter_easing = value; }
    void setHoverLeaveEasing(QEasingCurve::Type value) { hover_leave_easing = value; }
    void setHomePos(QPointF) override;
    void setSource(abstractPotion* c) { source = c; }
    //=============setters===============

};

#endif // POTIONPARENT_H
