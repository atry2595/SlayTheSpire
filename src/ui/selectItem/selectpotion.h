#ifndef SELECTPOTION_H
#define SELECTPOTION_H

#include <QObject>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "ui/textitem.h"
#include "ui/imageitem.h"
#include "items/potions/abstractpotion.h"
#include "core/setting.h"

class selectPotion : public QObject
{
    Q_OBJECT

private:

    BaseItem* parent;
    TextItem* header;
    QPushButton* overlay;
    QGraphicsProxyWidget* overlay_proxy;

    std::vector<BaseItem*> potion_parent;
    std::vector<abstractPotion*> potions;

    combatEvent* event;

    void execute();

    void potionSelected(abstractPotion*);
public:
    selectPotion(combatEvent* eve, std::vector<abstractPotion*> potion_source) ;


    BaseItem* getParent() { return parent; }

};

#endif // SELECTPOTION_H
