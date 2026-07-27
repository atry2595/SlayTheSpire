#ifndef DAMAGEEFFECT_H
#define DAMAGEEFFECT_H

#include "abstracteffect.h"
#include "ui/imageitem.h"
#include "getDamageEffect.h"

class damageEffect : public abstractEffect
{
private:
    BaseItem* parent;
    ImageItem* image = nullptr;
    std::vector<ImageItem*> borders;

public:
    damageEffect(cardID, QPointF pos, QSizeF size);
    damageEffect(entityID, QPointF pos, QSizeF size);
    ~damageEffect();

    BaseItem* getParent() { return parent; }

    void EntranceEffect() override;
    void ExitEffect() override {}
};

#endif // DAMAGEEFFECT_H
