#ifndef POWERPARENT_H
#define POWERPARENT_H

#include "ui/baseitem.h"
#include <QSequentialAnimationGroup>
#include "combat/combat_event.h"

class PowerParent : public BaseItem
{
    Q_OBJECT

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    abstractPower* source;
    combatEvent* eve;

public:
    PowerParent(combatEvent*,
                 abstractPower*,
                 QGraphicsItem* parent = nullptr,
                 QSizeF home_size = {0,0},
                 QPointF home_pos = {0,0});


    QSequentialAnimationGroup* attack_animation = nullptr;
    void activeAttackAnimation() { if (attack_animation) attack_animation->start(); }
};

#endif // POWERPARENT_H
