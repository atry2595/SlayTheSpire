#ifndef COMBATSETTING_H
#define COMBATSETTING_H

#include <QObject>
#include <QPushButton>
#include <QSlider>
#include <QGraphicsProxyWidget>
#include "combat/manageCombat/combatrewards.h"
#include "ui/textitem.h"
#include "ui/imageitem.h"
#include "combat/combat_event.h"
#include "entity/ironclad.h"

class combatSetting : public QObject
{
    Q_OBJECT

private:

    int x = 0;

    BaseItem* parent;
    TextItem* header;
    QPushButton* overlay;
    QGraphicsProxyWidget* overlay_proxy;

    QPushButton* abandon;
    QGraphicsProxyWidget* abandon_prxy;

    QPushButton* back;
    QGraphicsProxyWidget* back_prxy;

    TextItem* music_txt;
    TextItem* sfx_txt;

    QSlider* music;
    QGraphicsProxyWidget* music_prxy;

    QSlider* sfx;
    QGraphicsProxyWidget* sfx_prxy;


    combatEvent* event;

    bool eventFilter(QObject* obj, QEvent* eve) override;

    void execute();

public:
    combatSetting(combatEvent* eve) ;


    BaseItem* getParent() { return parent; }

};

#endif // COMBATSETTING_H
