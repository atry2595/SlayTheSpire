#ifndef STARTINGSELECT_H
#define STARTINGSELECT_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "assetsManager/imagemanager.h"
#include "assetsManager/soundmanager.h"
#include "combat/combat_event.h"
#include "core/setting.h"
#include "ui/imageitem.h"
#include <QHash>
#include <QPushButton>
#include <QGraphicsProxyWidget>

class startingSelect : public QWidget
{
    Q_OBJECT

public:
    startingSelect(QWidget *par = nullptr, combatEvent* eve = nullptr);
    ~startingSelect() override;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:


    combatEvent* eve;

    BaseItem* parent;

    QGraphicsView *combatView;
    QGraphicsScene *combatScene;

    skins selected_skin = skins::ironclad;
    cardTemplates selected_card = cardTemplates::common;

    QHash<skins, QGraphicsProxyWidget*> character_skin;
    QHash<cardTemplates, QGraphicsProxyWidget*> card_template;

    ImageItem* character;
    ImageItem* card;

    QGraphicsProxyWidget* start;

    void updateCard(cardTemplates tmp);
    void updateChar(skins sk);

    bool eventFilter(QObject* obj, QEvent* eve) override;
};

#endif // STARTINGSELECT_H
