#ifndef SELECTRELIC_H
#define SELECTRELIC_H

#include <QObject>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include "ui/textitem.h"
#include "ui/cards/cardtemplatecommon.h"
#include "ui/cards/cardtemplateuncommon.h"
#include "ui/cards/cardtemplatelegend.h"
#include "ui/cards/cardtemplaterare.h"
#include "core/setting.h"

class selectRelic : public QObject
{
    Q_OBJECT

private:

    bool selected = false;

    BaseItem* parent;
    TextItem* header;
    QPushButton* overlay;
    QGraphicsProxyWidget* overlay_proxy;

    std::vector<BaseItem*> relic_parent;
    std::vector<abstractRelic*> relics;

    combatEvent* event;

    void execute();

    void relicSelected(abstractRelic*);
public:
    selectRelic(combatEvent* eve, std::vector<abstractRelic*> relic_source) ;


    BaseItem* getParent() { return parent; }


};

#endif // SELECTRELIC_H
