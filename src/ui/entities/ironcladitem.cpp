#include "ironcladitem.h"
#include "entity/ironclad.h"
#include "items/potions/abstractpotion.h"
#include "ui/entities/getPotionIcon.h"
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
    hp_bar->setSize(IroncladItem::width, 30);

    hp_proxy = new QGraphicsProxyWidget(entity_parent);
    hp_proxy->setWidget(hp_bar);
    hp_proxy->setPos({0, IroncladItem::height + 60});


    //=======anim=========
    auto& anim = entity_parent->attack_animation;
    anim = new QSequentialAnimationGroup(entity_parent);
    anim->addAnimation(entity_parent->createMoveAnimation({pos.x() + IroncladItem::width/2, pos.y()}, 70, QEasingCurve::InQuart));
    anim->addAnimation(entity_parent->createMoveAnimation({pos.x(), pos.y()}, 321, QEasingCurve::OutQuart));

    //=======corners=========
    ImageItem* c1 = new ImageItem(entity_parent, {30, 30});
    c1->setPixmap(QPixmap(":/icon/corner.ico"));
    c1->setOpacity(0);
    c1->setZValue(9999);
    ImageItem* c2 = new ImageItem(entity_parent, {30, 30});
    c2->setPixmap(QPixmap(":/icon/corner.ico"));
    c2->setOpacity(0);
    c2->setRotation(90);
    c1->setZValue(9999);
    ImageItem* c3 = new ImageItem(entity_parent, {30, 30});
    c3->setPixmap(QPixmap(":/icon/corner.ico"));
    c3->setRotation(180);
    c3->setOpacity(0);
    c1->setZValue(9999);
    ImageItem* c4 = new ImageItem(entity_parent, {30, 30});
    c4->setPixmap(QPixmap(":/icon/corner.ico"));
    c4->setRotation(270);
    c4->setOpacity(0);
    c1->setZValue(9999);

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
        TextItem* p = new TextItem(entity_parent, {35, 35}, QPointF(35*i, IroncladItem::height + 60 + 30));
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


    //========potions=========
    for (auto item:potions){
        delete item;
    }
    potions.clear();

    ironclad* player = dynamic_cast<ironclad*>(entity_source);

    for (int i = 0; i < std::min(3, (int)player->get_potion_list().size()); i++) {
        ImageItem* p = new ImageItem(entity_parent, {58, 58}, QPointF(-60, 50 * (i+1) + 28 * i));
        auto pot = player->get_potion_list()[i];
        p->setPixmap(getPotionIcon(pot->get_ID()));
        potions.push_back(p);
    }

}
