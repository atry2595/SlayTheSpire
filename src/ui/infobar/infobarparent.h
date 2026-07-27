#ifndef INFOBARPARENT_H
#define INFOBARPARENT_H

#include "ui/baseitem.h"


enum class barAlign {
    left,
    right
};

class infobarParent : public BaseItem
{
    Q_OBJECT

private:
    barAlign align = barAlign::left;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

public:
    infobarParent(QGraphicsItem* parent = nullptr,barAlign al = barAlign::left , QSizeF home_size = {1600, 900});
    void Entrance();
    void Exit();

};

#endif // INFOBARPARENT_H
