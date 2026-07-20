#ifndef ENEMYITEM_H
#define ENEMYITEM_H

#include "abstractentityitem.h"
#include "ui/entities/getvisualdata.h"

class EnemyItem : public abstractEntityItem
{
    Q_OBJECT
    qreal width;
    qreal height;
    EntityAnimType anim_type;
    combatEvent* eve;
public:
    EnemyItem(combatEvent*, abstractEntity* source, QPointF pos, qreal zValue);

    void updateEntity();
};

#endif // ENEMYITEM_H
