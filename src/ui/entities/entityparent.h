#ifndef ENTITYPARENT_H
#define ENTITYPARENT_H

#include "ui/baseitem.h"

class EntityParent : public BaseItem
{
    Q_OBJECT

private:
    bool is_enemy = false;
    QPropertyAnimation* attack_animation = nullptr;

public:
    EntityParent(QGraphicsItem* parent = nullptr,
                 QSizeF home_size = {0,0},
                 QPointF home_pos = {0,0});

    void setIsEnemy(bool enmy) { is_enemy = enmy; }
    bool getIsEnemy() { return is_enemy; }

    void activeAttackAnimation() { attack_animation->start(); }
};

#endif // ENTITYPARENT_H
