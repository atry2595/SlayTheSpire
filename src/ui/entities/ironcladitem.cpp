#include "ironcladitem.h"
#include "entity/ironclad.h"
#include "items/potions/abstractpotion.h"
#include "assetsManager/imagemanager.h"
#include "core/setting.h"
#include <QSequentialAnimationGroup>

IroncladItem::IroncladItem(combatEvent* event, abstractEntity* source, QPointF pos, qreal zValue)
    :abstractEntityItem(source, pos, {IroncladItem::width, IroncladItem::height + 110}, zValue)
    ,eve(event)
{

    auto mng = imageManager::instance();
    //=======parent=========
    entity_parent = new EntityParent(eve, entity_source, nullptr, entity_size, entity_pos);
    entity_parent->setZValue(0 + zValue);



    //=======intent========
    intent = nullptr;


    //=======image========
    entity_image = new ImageItem(entity_parent, {IroncladItem::width, IroncladItem::height}, {0, 50});
    entity_image->setPixmap(mng.getIroncladImage(combat_data::selected_character)); // switch case
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
    c1->setPixmap(mng.getEffectImage("corner"));
    c1->setOpacity(0);
    c1->setZValue(9999);
    ImageItem* c2 = new ImageItem(entity_parent, {30, 30});
    c2->setPixmap(mng.getEffectImage("corner"));
    c2->setOpacity(0);
    c2->setRotation(90);
    c1->setZValue(9999);
    ImageItem* c3 = new ImageItem(entity_parent, {30, 30});
    c3->setPixmap(mng.getEffectImage("corner"));
    c3->setRotation(180);
    c3->setOpacity(0);
    c1->setZValue(9999);
    ImageItem* c4 = new ImageItem(entity_parent, {30, 30});
    c4->setPixmap(mng.getEffectImage("corner"));
    c4->setRotation(270);
    c4->setOpacity(0);
    c1->setZValue(9999);

    updateEntity();

}


void IroncladItem::updateEntity() {

    auto mng = imageManager::instance();

    //=======hpBar=======
    hp_bar->setMaxHp(entity_source->get_max_hp());
    hp_bar->setHp(entity_source->get_hp());
    hp_bar->setShield(entity_source->get_block());


    //======powers=======
    for (auto item: powers_prnt) {
        delete item;
    }
    powers_prnt.clear();

    for (auto item: powers) {
        delete item;
    }
    powers.clear();

    for (int i = 0; i < entity_source->get_power_list().size(); i++){
        auto pwr = entity_source->get_power_list()[i];

        PowerParent* pp =  new PowerParent(eve, pwr, entity_parent, {35, 35}, QPointF(35*i, height + 60 + 30));
        powers_prnt.push_back(pp);

        TextItem* p = new TextItem(entity_parent, {35, 35}, QPointF(35*i, IroncladItem::height + 60 + 30));
        p->setBackground(mng.getPowerIcon(pwr->get_id()));

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

    for (auto item : potion_parents){
        delete item;
    }
    potion_parents.clear();

    for (int i = 0; i < std::min(3, (int)player->get_potion_list().size()); i++) {
        auto p_p = new PotionParent(eve, player->get_potion_list()[i], entity_parent, {58, 58}, QPointF(-60, 50 * (i+1) + 28 * i), 10);
        potion_parents.push_back(p_p);
        ImageItem* p = new ImageItem(potion_parents[i], {58, 58}, {0, 0});
        auto pot = player->get_potion_list()[i];
        p->setPixmap(mng.getPotionIcon(pot->get_ID()));
        potions.push_back(p);
    }

}
