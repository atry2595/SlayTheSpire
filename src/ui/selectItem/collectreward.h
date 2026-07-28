#ifndef COLLECTREWARD_H
#define COLLECTREWARD_H

#include <QObject>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "combat/manageCombat/combatrewards.h"
#include "ui/textitem.h"
#include "ui/imageitem.h"
#include "combat/combat_event.h"
#include "entity/ironclad.h"

class collectReward : public QObject
{
    Q_OBJECT

private:

    bool selected = false;

    int x = 0;

    BaseItem* parent;
    TextItem* header;
    QPushButton* overlay;
    QGraphicsProxyWidget* overlay_proxy;

    std::vector<BaseItem*> all_base;

    QPushButton* btn;
    QGraphicsProxyWidget* prxy;

    combatEvent* event;
    combatReward* rew;
    ironclad* player;

    bool eventFilter(QObject* obj, QEvent* eve) override;

    void execute();

public:
    collectReward(combatEvent* eve, combatReward* reward, ironclad* plyr) ;


    BaseItem* getParent() { return parent; }

};

#endif // COLLECTREWARD_H
