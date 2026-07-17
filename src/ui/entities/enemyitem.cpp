#include "enemyitem.h"
#include "ui/entities/getIntentIcon.h"
#include "ui/entities/getCharacterPixmap.h"
#include "entity/abstractenemy.h"
#include <QSequentialAnimationGroup>

EnemyItem::EnemyItem(abstractEntity* source, QPointF pos, qreal zValue)
    : width(getEntityVisual(source->get_ID()).size.width())
    , height(getEntityVisual(source->get_ID()).size.height())
    , anim_type(getEntityVisual(source->get_ID()).anim)
    , abstractEntityItem(source, pos, QSizeF(getEntityVisual(source->get_ID()).size.width(), getEntityVisual(source->get_ID()).size.height() + 120), zValue) {

    //=======parent=========
    entity_parent = new EntityParent(nullptr, entity_size, entity_pos);



    //=======image========
    entity_image = new ImageItem(entity_parent, {width, height}, {0, 50});
    entity_image->setPixmap(getCharacterPixmap(source->get_ID()));
    QSequentialAnimationGroup* gr = new QSequentialAnimationGroup(entity_image);


    switch (anim_type)  {
    case EntityAnimType::Humanoid: {
        QRectF dest = {entity_image->pos() + QPointF(0, -8), entity_image->size() + QSizeF(0, 8)};
        QRectF orig = {entity_image->pos(), entity_image->size()};
        gr->addAnimation(entity_image->createGeometryAnimation(dest, 1000, QEasingCurve::InOutSine));
        gr->addAnimation(entity_image->createGeometryAnimation(orig, 1000, QEasingCurve::InOutSine));
        break;
    }

    case EntityAnimType::Floating: {
        QPointF dest = {entity_image->pos() + QPointF(0, -8)};
        QPointF orig = {entity_image->pos()};
        gr->addAnimation(entity_image->createMoveAnimation(dest, 1000, QEasingCurve::InOutSine));
        gr->addAnimation(entity_image->createMoveAnimation(orig, 1000, QEasingCurve::InOutSine));
        break;
    }

    case EntityAnimType::Slime: {
        QRectF dest = {entity_image->pos() + QPointF(0, -8), entity_image->size() + QSizeF(0, 8)};
        QRectF orig = {entity_image->pos(), entity_image->size()};
        gr->addAnimation(entity_image->createGeometryAnimation(dest, 1000, QEasingCurve::OutElastic));
        gr->addAnimation(entity_image->createGeometryAnimation(orig, 1000, QEasingCurve::InOutSine));
        break;
    }

    case EntityAnimType::Louse: {
        QRectF dest = {entity_image->pos() + QPointF(0, -4), entity_image->size() + QSizeF(0, 4)};
        QRectF orig = {entity_image->pos() + QPointF(-4, 0), entity_image->size() + QSizeF(8, 0)};
        gr->addAnimation(entity_image->createGeometryAnimation(dest, 1000, QEasingCurve::InOutQuad));
        gr->addAnimation(entity_image->createGeometryAnimation(orig, 1000, QEasingCurve::InOutQuad));
        break;
    }

    case EntityAnimType::Book: {
        QRectF dest = {entity_image->pos() + QPointF(-5, -10), entity_image->size() + QSizeF(10, 10)};
        QRectF orig = {entity_image->pos(), entity_image->size()};
        gr->addAnimation(entity_image->createGeometryAnimation(dest, 1000, QEasingCurve::InOutQuad));
        gr->addAnimation(entity_image->createGeometryAnimation(orig, 1000, QEasingCurve::InOutQuad));
        break;
    }
    }
    gr->setLoopCount(-1);
    gr->start();


    //=======hpBar========
    hp_bar = new SimpleHpBar();
    hp_bar->setSize(width, 30);

    hp_proxy = new QGraphicsProxyWidget(entity_parent);
    hp_proxy->setWidget(hp_bar);
    hp_proxy->setPos({0, height + 60});


    //=======anim=========
    auto& anim = entity_parent->attack_animation;
    anim = new QSequentialAnimationGroup(entity_parent);
    anim->addAnimation(entity_parent->createMoveAnimation({pos.x() - height / 2, pos.y()}, 70, QEasingCurve::InQuart));
    anim->addAnimation(entity_parent->createMoveAnimation({pos.x(), pos.y()}, 321, QEasingCurve::OutQuart));


    updateEntity();

}


void EnemyItem::updateEntity() {

    qDebug() << "del dar moyad darad khane, majroh gardad cho zani hardam shane";

    //=======intent======
    if (intent) delete intent;
    intent = new TextItem(entity_parent, {45, 45}, {((width - 45) / 2), -8});
    abstractEnemy* enmy = dynamic_cast<abstractEnemy*>(entity_source);
    auto intnt = enmy->get_intent_list()[enmy->get_current_move()];

    intent->setBackground(getIntentIcon(intnt));
    if (intnt.damage) {
        QString txt = QString::number(intnt.damage);
        if (intnt.repeat > 1) {
            txt += "x";
            txt += QString::number(intnt.repeat);
        }
        intent->setText(txt);
        intent->setColor(Qt::white);
        intent->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
        intent->setBorder(true);
        QFont fnt;
        fnt.setFamily(Fonts::Cascadia);
        fnt.setPixelSize(16);
        fnt.setBold(true);
        intent->setFont(fnt);
    }

    QSequentialAnimationGroup* gr = new QSequentialAnimationGroup(intent);


    gr->addAnimation(intent->createMoveAnimation({((width - 45) / 2), -8 -10}, 1000, QEasingCurve::InOutSine));
    gr->addAnimation(intent->createMoveAnimation({((width - 45) / 2), -8}, 1000, QEasingCurve::InOutSine));
    gr->setLoopCount(-1);
    gr->start();


    //=======hpBar=======
    hp_bar->setMaxHp(entity_source->get_max_hp());
    hp_bar->setHp(entity_source->get_hp());
    hp_bar->setShield(entity_source->get_block());


    //======powers=======
    for (auto item: powers) {
        delete item;
    }
    powers.clear();

    for (int i = 0; i < entity_source->get_power_list().size(); i++){
        TextItem* p = new TextItem(entity_parent, {35, 35}, QPointF(35*i, height + 60 + 30));
        auto pwr = entity_source->get_power_list()[i];
        p->setBackground(getPowerIcon(pwr->get_id()));

        if (pwr->get_amount() != 1){
            p->setText(QString::number(pwr->get_amount()));
            p->setColor((pwr->get_amount() > 1) ? (Qt::green) : (Qt::red));
            p->setAlignment(Qt::AlignBottom | Qt::AlignRight);
            p->setBorder(true);
            QFont fnt;
            fnt.setFamily(Fonts::Cascadia);
            fnt.setPixelSize(17);
            fnt.setBold(true);
            p->setFont(fnt);
        }
        powers.push_back(p);
    }

}
