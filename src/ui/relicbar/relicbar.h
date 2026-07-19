#ifndef RELICBAR_H
#define RELICBAR_H

#include <QObject>
#include "ui/imageitem.h"
#include "items/relics/abstractrelic.h"

class RelicBar : public QObject
{
    Q_OBJECT

    std::vector<ImageItem*> rlcs_image;
    BaseItem* parent = nullptr;

public:
    RelicBar(std::vector<abstractRelic*>);

    BaseItem* getParent() { return parent; }
};

#endif // RELICBAR_H
