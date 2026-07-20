#ifndef RELICPARENT_H
#define RELICPARENT_H

#include "ui/baseitem.h"
#include <QSequentialAnimationGroup>
#include "combat/combat_event.h"

class RelicParent : public BaseItem
{
    Q_OBJECT

private:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    abstractRelic* source;
    combatEvent* eve;

public:
    RelicParent(combatEvent*,
                 abstractRelic*,
                 QGraphicsItem* parent = nullptr,
                 QSizeF home_size = {0,0},
                 QPointF home_pos = {0,0});


    QSequentialAnimationGroup* attack_animation = nullptr;
    void activeAttackAnimation() { if (attack_animation) attack_animation->start(); }
};

#endif // RELICPARENT_H
