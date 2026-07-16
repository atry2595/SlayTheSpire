#include "abstractentityitem.h"
#include <QParallelAnimationGroup>

abstractEntityItem::abstractEntityItem(abstractEntity* source, QPointF pos, QSizeF size, qreal zValue)
    :entity_source(source),
        entity_pos(pos),
        entity_size(size),
        z_value(zValue)
{}

abstractEntityItem::~abstractEntityItem() {
    delete entity_image;
    delete entity_name;
    delete intent;
    delete hp_proxy;
    for (auto item : powers) delete item;
    powers.clear();
    delete entity_parent;
}


void abstractEntityItem::dieAnim() {
    if (!entity_parent) return;

    QSequentialAnimationGroup* mainAnim =  new QSequentialAnimationGroup(entity_parent);

    QParallelAnimationGroup* anim = new QParallelAnimationGroup(entity_parent);

    QSequentialAnimationGroup* moveGr = new QSequentialAnimationGroup(entity_parent);


    QPointF dest1 = entity_pos + QPointF(25, 0);
    QPointF dest2 = entity_pos - QPointF(25, 0);

    moveGr->addAnimation(entity_parent->createMoveAnimation(dest1, 80, QEasingCurve::OutCubic));
    moveGr->addAnimation(entity_parent->createMoveAnimation(dest2, 160, QEasingCurve::Linear));
    moveGr->addAnimation(entity_parent->createMoveAnimation(dest1, 160, QEasingCurve::Linear));
    moveGr->addAnimation(entity_parent->createMoveAnimation(dest2, 160, QEasingCurve::Linear));
    moveGr->addAnimation(entity_parent->createMoveAnimation(entity_pos, 80, QEasingCurve::InCubic));

    anim->addAnimation(moveGr);
    anim->addAnimation(entity_parent->createOpacityAnimation(0, 640));

    mainAnim->addPause(100);
    mainAnim->addAnimation(anim);

    mainAnim->start();

}
void abstractEntityItem::escapeAnim() {
    if (!entity_parent) return;

    qreal img_x = entity_image->pos().x();
    qreal img_y = entity_image->pos().y();

    QSequentialAnimationGroup* animGr = new QSequentialAnimationGroup(entity_parent);


    qreal xbck = img_x + 25 * (-1 * (entity_source->get_ID() == entityID::ironclad));
    auto anim1 = entity_image->createMoveAnimation( {xbck, img_y}, 250);
    animGr->addAnimation(anim1);

    animGr->addPause(100);

    qreal xpnt = 1700 - 2300 * (entity_source->get_ID() == entityID::ironclad);
    animGr->addAnimation(entity_parent->createMoveAnimation({xpnt, entity_pos.y()}, 1000));

    connect(anim1, &QPropertyAnimation::finished, [this]{
        QTransform t;
        t.translate(entity_size.width(), 0);
        t.scale(-1, 1);

        entity_image->setTransform(t);
    });

    animGr->start();

}



void abstractEntityItem::setHighlight(bool b) {
    entity_image->setHighlight(b);
}
void abstractEntityItem::setHighlightColor(QColor clr){
    entity_image->setHighlightColor(clr);
}
