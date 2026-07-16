#include "damageeffect.h"
#include <QSequentialAnimationGroup>

damageEffect::damageEffect(cardID id, QPointF pos, QSizeF size)
{
    auto inf = getDamageEffect(id);

    qreal eff_width = size.width() * 1.5;
    qreal eff_height = eff_width * inf.size.height() / inf.size.width();
    qreal eff_x = pos.x() - size.width() * 0.1;
    qreal eff_y = pos.y() + (size.height() - eff_height)/2;

    parent = new BaseItem(nullptr, QSizeF(eff_width, eff_height), QPointF(eff_x, eff_y));
    parent->setZValue(9999);
    parent->setOpacity(0);

    image = new ImageItem(parent, QSizeF(eff_width, eff_height), QPointF(0,0));
    image->setPixmap(inf.image);

}


damageEffect::damageEffect(entityID id, QPointF pos, QSizeF size)
{
    auto inf = getDamageEffect(id);

    qreal eff_width = size.width() * 1.5;
    qreal eff_height = eff_width * inf.size.height() / inf.size.width();
    qreal eff_x = pos.x() - size.width() * 0.1;
    qreal eff_y = pos.y() + (size.height() - eff_height)/2;
    parent = new BaseItem(nullptr, QSizeF(eff_width, eff_height), QPointF(eff_x, eff_y));
    parent->setZValue(9999);
    parent->setOpacity(0);

    image = new ImageItem(parent, QSizeF(eff_width, eff_height), QPointF(0,0));
    image->setPixmap(inf.image);

}

damageEffect::~damageEffect() {
    delete image;
    delete parent;
}

void damageEffect::EntranceEffect() {

    QSequentialAnimationGroup* gr = new QSequentialAnimationGroup(parent);

    gr->addAnimation(parent->createOpacityAnimation(1, 50));
    gr->addPause(300);
    gr->addAnimation(parent->createOpacityAnimation(0, 300));

    gr->start();
}