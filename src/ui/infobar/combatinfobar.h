#ifndef COMBATINFOBAR_H
#define COMBATINFOBAR_H

#include "abstractinfobar.h"
#include "items/relics/abstractrelic.h"
#include "items/potions/abstractpotion.h"
#include "items/powers/abstractpower.h"
#include "entity/abstractentity.h"

class CombatInfoBar : public abstractInfoBar
{
    Q_OBJECT

    BaseItem* section;
    BaseItem* border;

    ImageItem* item_image;
    TextItem* item_name;
    TextItem* item_description;
    TextItem* item_story;

    void initial();

public:
    CombatInfoBar(abstractRelic*);
    CombatInfoBar(abstractPotion*);
    CombatInfoBar(abstractPower*);
    CombatInfoBar(abstractEntity*);
    ~CombatInfoBar();

    auto getParent() { return parent; }
};

#endif // COMBATINFOBAR_H
