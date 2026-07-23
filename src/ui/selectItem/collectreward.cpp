#include "collectreward.h"
#include "core/setting.h"
#include <QTimer>
#include "assetsManager/imagemanager.h"
#include "items/potions/abstractpotion.h"
#include "items/relics/abstractrelic.h"
#include "core/setting.h"

collectReward::collectReward(combatEvent* eve, combatReward* reward, ironclad* plyr)
    :event(eve)
    ,rew(reward)
    ,player(plyr)
{
    auto mng = imageManager::instance();

    QString blank_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;}"
        "QPushButton:hover{background:transparent;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;


    parent = new BaseItem(nullptr, {1650, 950}, {0, 0});
    parent->setBackColor(QColor::fromRgba(qRgba(0, 0, 0, 180)));
    parent->setZValue(13100);
    parent->setOpacity(0);

    overlay = new QPushButton();
    overlay->setFixedSize(1650, 950);
    overlay->setDisabled(true);
    overlay->setStyleSheet(blank_css);
    overlay_proxy = new QGraphicsProxyWidget(parent);
    overlay_proxy->setWidget(overlay);
    overlay_proxy->setPos(0, 0);

    header = new TextItem(parent, {1000, 100}, {300, 50});
    header->setText(tr("Rewards!"));
    QFont f;
    f.setFamily(Fonts::Cascadia);
    f.setPixelSize(45);
    header->setFont(f);

    QFont txt;
    txt.setFamily(Fonts::Cascadia);
    txt.setPixelSize(20);

    if (rew->get_returned_gold()) {
        auto rgp = new BaseItem(parent, {400, 70}, QPointF(600, 175 + 90 * all_base.size()));
        auto rgi = new ImageItem(rgp, {70, 70}, {0, 0});
        rgi->setPixmap(mng.getIcon("coin"));
        auto rgt = new TextItem(rgp, {300, 70}, {100, 0});
        rgt->setText(QString::number(rew->get_returned_gold()) + tr(" gold (stolen back)"));
        rgt->setFont(txt);
        rgt->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        all_base.push_back(rgp);
    }

    if (rew->get_gold()) {
        auto gp = new BaseItem(parent, {400, 70}, QPointF(600, 175 + 90 * all_base.size()));
        auto gi = new ImageItem(gp, {70, 70}, {0, 0});
        gi->setPixmap(mng.getIcon("coin"));
        auto gt = new TextItem(gp, {300, 70}, {100, 0});
        gt->setText(QString::number(rew->get_gold()) + tr(" gold"));
        gt->setFont(txt);
        gt->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        all_base.push_back(gp);
    }

    for (auto item : rew->get_potion()) {
        auto potp = new BaseItem(parent, {400, 70}, QPointF(600, 175 + 90 * all_base.size()));
        auto poti = new ImageItem(potp, {70, 70}, {0, 0});
        poti->setPixmap(mng.getPotionIcon(item->get_ID()));
        auto pott = new TextItem(potp, {300, 70}, {100, 0});
        pott->setText(item->get_name());
        pott->setFont(txt);
        pott->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        all_base.push_back(potp);
    }

    for (auto item : rew->get_relic()) {
        auto rlcp = new BaseItem(parent, {400, 70}, QPointF(600, 175 + 90 * all_base.size()));
        auto rlci = new ImageItem(rlcp, {70, 70}, {0, 0});
        rlci->setPixmap(mng.getRelicIcon(item->get_id()));
        auto rlct = new TextItem(rlcp, {300, 70}, {100, 0});
        rlct->setText(item->get_name());
        rlct->setFont(txt);
        rlct->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        all_base.push_back(rlcp);
    }

    for (int i = 0; i < rew->get_cards().size(); i++) {
        auto crdp = new BaseItem(parent, {400, 70}, QPointF(600, 175 + 90 * all_base.size()));
        auto crdi = new ImageItem(crdp, {45, 70}, {12.5, 0});
        crdi->setPixmap(mng.getCardBack(combat_data::selected_card_template));
        auto crdt = new TextItem(crdp, {300, 70}, {100, 0});
        crdt->setText(tr("Add a card to your deck"));
        crdt->setFont(txt);
        crdt->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
        all_base.push_back(crdp);
    }

    btn = new QPushButton();
    btn->setFixedSize(200, 100);
    btn->setFont(f);
    btn->setText(tr("Confirm"));
    prxy = new QGraphicsProxyWidget(parent);
    prxy->setWidget(btn);
    prxy->setPos(700, 900 - 150);

    parent->fadeTo(1, 500, QEasingCurve::OutSine);

    connect(btn, &QPushButton::clicked, this, &collectReward::execute);
}

void collectReward::execute() {
    player->earn_coin(rew->get_gold());
    player->earn_coin(rew->get_returned_gold());
    for (auto item : rew->get_potion()) player->potion_list_add(item);
    game_action g(event);
    for (auto item : rew->get_relic()) player->add_relic(g, item);

    parent->fadeTo(0, 500);

    if (rew->get_cards().size()){
        emit event->selectCard(rew->get_cards()[0]);

        connect(event, &combatEvent::cardSelected, this, [=](abstractCard* card){
            for (auto item : rew->get_cards()[0]) {
                if (item != card) delete item;
            }
            player->deck_add(card);
            emit event->nextAction();
            delete parent;
            this->deleteLater();
        });
    }
}
