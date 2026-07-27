#ifndef IRONCLADITEM_H
#define IRONCLADITEM_H

#include "abstractentityitem.h"
#include "ui/entities/potionparent.h"

class IroncladItem : public abstractEntityItem
{
    Q_OBJECT
    constexpr static int width = 300;
    constexpr static int height = 214;

    std::vector<PotionParent*> potion_parents;
    std::vector<ImageItem*> potions;

    combatEvent* eve;

public:
    IroncladItem(combatEvent*, abstractEntity* source, QPointF pos, qreal zValue);

    void updateEntity();
};

#endif // IRONCLADITEM_H
