#ifndef ENTITYPARENT_H
#define ENTITYPARENT_H

#include "ui/baseitem.h"
#include <QSequentialAnimationGroup>
#include "combat/combat_event.h"

class EntityParent : public BaseItem
{
    Q_OBJECT

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    abstractEntity* source;
    combatEvent* eve;

public:
    EntityParent(combatEvent*,
                 abstractEntity*,
                 QGraphicsItem* parent = nullptr,
                 QSizeF home_size = {0,0},
                 QPointF home_pos = {0,0});


    QSequentialAnimationGroup* attack_animation = nullptr;
    void activeAttackAnimation() { if (attack_animation) attack_animation->start(); }
};

#endif // ENTITYPARENT_H
