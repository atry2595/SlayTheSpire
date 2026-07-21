#ifndef SELECTCARD_H
#define SELECTCARD_H

#include <QObject>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "ui/textitem.h"
#include "ui/cards/cardtemplatecommon.h"
#include "ui/cards/cardtemplateuncommon.h"
#include "ui/cards/cardtemplatelegend.h"
#include "ui/cards/cardtemplaterare.h"
#include "core/setting.h"

class selectCard : public QObject
{
    Q_OBJECT

private:
    int current_min = 0;
    int current_max = 4;

    int count;

    BaseItem* parent;
    TextItem* header;
    QPushButton* overlay;
    QGraphicsProxyWidget* overlay_proxy;
    std::vector<abstractCardTemplate*> cards;
    QPushButton* next_button;
    QPushButton* pre_button;
    QGraphicsProxyWidget* next_proxy;
    QGraphicsProxyWidget* pre_proxy;

    combatEvent* event;

    void execute();

public:
    selectCard(combatEvent* eve, std::vector<abstractCard*> card_source) ;


    BaseItem* getParent() { return parent; }
    std::vector<abstractCardTemplate*> getCards() { return cards; }

private slots:
    void nextCards();
    void preCards();
    void cardSelected(CardParent*);

};

#endif // SELECTCARD_H
