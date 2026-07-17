#ifndef COMBATTOPBAR_H
#define COMBATTOPBAR_H

#include <QObject>
#include "entity/ironclad.h"
#include "ui/imageitem.h"
#include "ui/textitem.h"
#include "ui/entities/simplehpbar.h"
#include <QPushButton>


class CombatTopBar : public QObject
{
    Q_OBJECT

private:
    combatEvent* eve;
    ironclad* player;

    BaseItem* parent;
    ImageItem* gold_image;
    TextItem* gold_amount;
    ImageItem* hp_image;
    TextItem* hp_amount;
    SimpleHpBar* energy_bar = nullptr;
    QGraphicsProxyWidget* energy_proxy = nullptr;
    QPushButton* end_btn;
    QGraphicsProxyWidget* btn_proxy = nullptr;

public:
    CombatTopBar(combatEvent* eve, ironclad* player);

    auto getParent() { return parent; }

    void updateBar();
};

#endif // COMBATTOPBAR_H
