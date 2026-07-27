#ifndef ABSTRACTINFOBAR_H
#define ABSTRACTINFOBAR_H

#include "ui/imageitem.h"
#include "ui/textitem.h"
#include "ui/infobar/infobarparent.h"

#include <QObject>


class abstractInfoBar : public QObject
{
    Q_OBJECT

    QSizeF size = {400, 900};

protected:
    infobarParent* parent = nullptr;

public:
    abstractInfoBar() {};

    inline void Entrance() { parent->Entrance(); }

    auto getParent() { return parent;}
};

#endif // ABSTRACTINFOBAR_H
