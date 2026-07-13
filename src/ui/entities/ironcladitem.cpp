#include "ironcladitem.h"
#include <QSequentialAnimationGroup>

IroncladItem::IroncladItem(abstractEntity* source, QPointF pos, qreal zValue)
    :abstractEntityItem(source, pos, {IroncladItem::width, IroncladItem::height + 110}, zValue)
{
    //=======parent=========
    entity_parent = new EntityParent(nullptr, entity_size, entity_pos);



    //=======intent========
    intent = nullptr;


    //=======image========
    entity_image = new ImageItem(entity_parent, {IroncladItem::width, IroncladItem::height}, {0, 50});
    entity_image->setPixmap(QPixmap(":/image/characters/ironclad1.png")); // switch case
    QSequentialAnimationGroup* gr = new QSequentialAnimationGroup(entity_image);

    QRectF dest = {entity_image->pos() + QPointF(0, -8), entity_image->size() + QSizeF(0, 8)};
    QRectF orig = {entity_image->pos(), entity_image->size()};

    gr->addAnimation(entity_image->createGeometryAnimation(dest, 1000, QEasingCurve::InOutSine));
    gr->addAnimation(entity_image->createGeometryAnimation(orig, 1000, QEasingCurve::InOutSine));
    gr->setLoopCount(-1);
    gr->start();


    //=======hpBar========
    hp_bar = new SimpleHpBar();
    hp_bar->setSize(IroncladItem::width, 15);

    hp_proxy = new QGraphicsProxyWidget(entity_parent);
    hp_proxy->setWidget(hp_bar);
    hp_proxy->setPos({0, IroncladItem::height + 50});


    //=======anim=========
    auto& anim = entity_parent->attack_animation;
    anim = new QSequentialAnimationGroup(entity_parent);
    anim->addAnimation(entity_parent->createMoveAnimation({pos.x() + IroncladItem::width/2, pos.y()}, 321, QEasingCurve::InQuart));
    anim->addAnimation(entity_parent->createMoveAnimation({pos.x(), pos.y()}, 321, QEasingCurve::OutQuart));


    updateEntity();

}


void IroncladItem::updateEntity() {

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
        TextItem* p = new TextItem(entity_parent, {35, 35}, QPointF(35*i, IroncladItem::height + 50 + 20));
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
