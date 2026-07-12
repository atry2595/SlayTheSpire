#include "ironcladitem.h"

IroncladItem::IroncladItem(abstractEntity* source, QPointF pos, qreal zValue)
    :abstractEntityItem(source, pos, {300, 214 + 110}, zValue)
{
    //=======parent=========
    entity_parent = new EntityParent(nullptr, entity_size, entity_pos);



    //=======intent========
    intent_icon = nullptr;


    //=======image========
    entity_image = new ImageItem(entity_parent, {300, 214}, {0, 50});
    entity_image->setPixmap(QPixmap(":/image/characters/ironclad1.png")); // switch case


    //=======hpBar========
    hp_bar = new SimpleHpBar();
    hp_bar->setSize(300, 30);

    hp_proxy = new QGraphicsProxyWidget(entity_parent);
    hp_proxy->setWidget(hp_bar);
    hp_proxy->setPos({0, 214 + 50});


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
        TextItem* p = new TextItem(entity_parent, {30, 30}, QPointF(30*i, 214 + 50 + 30));
        auto pwr = entity_source->get_power_list()[i];
        p->setBackground(getPowerIcon(pwr->get_id()));

        if (pwr->get_amount() != 1){
            p->setText(QString::number(pwr->get_amount()));
            p->setColor(Qt::black);
            QFont fnt;
            fnt.setFamily(Fonts::Cascadia);
            fnt.setPixelSize(8);
            p->setFont(fnt);
        }
        powers.push_back(p);
    }

}
