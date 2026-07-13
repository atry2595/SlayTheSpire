#ifndef ENTITYPARENT_H
#define ENTITYPARENT_H

#include "ui/baseitem.h"
#include <QSequentialAnimationGroup>

class EntityParent : public BaseItem
{
    Q_OBJECT

private:


public:
    EntityParent(QGraphicsItem* parent = nullptr,
                 QSizeF home_size = {0,0},
                 QPointF home_pos = {0,0});


    QSequentialAnimationGroup* attack_animation = nullptr;
    void activeAttackAnimation() { if (attack_animation) attack_animation->start(); }
};

#endif // ENTITYPARENT_H
