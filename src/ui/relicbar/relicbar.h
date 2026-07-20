#ifndef RELICBAR_H
#define RELICBAR_H

#include <QObject>
#include "ui/imageitem.h"
#include "items/relics/abstractrelic.h"
#include "relicparent.h"

class RelicBar : public QObject
{
    Q_OBJECT

    BaseItem* parent = nullptr;

    std::vector<RelicParent*> rlcs_parents;
    std::vector<ImageItem*> rlcs_image;

public:
    RelicBar(combatEvent* event, std::vector<abstractRelic*>);

    BaseItem* getParent() { return parent; }
};

#endif // RELICBAR_H
