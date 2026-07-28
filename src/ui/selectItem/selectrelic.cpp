#include "selectrelic.h"
#include "core/setting.h"
#include <QTimer>
#include "assetsManager/imagemanager.h"
#include "assetsManager/soundmanager.h"
#include "items/relics/abstractrelic.h"

selectRelic::selectRelic(combatEvent* eve, std::vector<abstractRelic*> relic_source)
    :event(eve)
    ,relics(relic_source)
{

    QString blank_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;}"
        "QPushButton:hover{background:transparent;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;

    parent = new BaseItem(nullptr, {1650, 950}, {0, 0});
    parent->setBackColor(QColor::fromRgba(qRgba(0, 0, 30, 203)));
    parent->setZValue(13400);
    parent->setOpacity(0);

    overlay = new QPushButton();
    overlay->setFixedSize(1650, 950);
    overlay->setDisabled(true);
    overlay->setStyleSheet(blank_css);
    overlay_proxy = new QGraphicsProxyWidget(parent);
    overlay_proxy->setWidget(overlay);
    overlay_proxy->setPos(0, 0);

    header = new TextItem(parent, {1000, 200}, {300, 50});
    header->setText(tr("Choose a Relic:"));
    QFont f;
    f.setFamily(Fonts::Cascadia);
    f.setPixelSize(40);
    header->setFont(f);

    for (auto item : relics) {
        auto par = new BaseItem(parent, {200, 300});
        auto img = new ImageItem(par, {150, 150}, {25, 0});
        img->setPixmap(imageManager::instance().getRelicIcon(item->get_id()));

        auto name = new TextItem(par, {200, 50}, {0, 150});
        name->setText(item->get_name());
        QFont f1; f1.setFamily(Fonts::Cascadia); f1.setPixelSize(25);
        name->setFont(f1);

        auto des = new TextItem(par, {200, 100}, {0, 200});
        QFont f2; f2.setFamily(Fonts::Cascadia); f2.setPixelSize(17);
        des->setText(item->get_description());
        des->setFont(f2);

        auto btn = new QPushButton();
        btn->setFixedSize(200, 300);
        btn->setStyleSheet(blank_css);
        connect(btn, &QPushButton::clicked, this, [=](){relicSelected(item);});
        auto prx = new QGraphicsProxyWidget(par);
        prx->setWidget(btn);
        relic_parent.push_back(par);
    }

    execute();
}

void selectRelic::execute() {

    for (int i = 0; i < 3; i++){

        qreal x = 400 + 302 * i;

        relic_parent[i]->setPos(x, 300);

    }

    parent->fadeTo(1, 500);
}

void selectRelic::relicSelected(abstractRelic* rlc) {

    if (selected) return;
    selected = true;

    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    emit event->relicSelected(rlc);
    parent->fadeTo(0, 500, QEasingCurve::OutSine);
    QTimer::singleShot(500, [=](){delete parent;});
    QTimer::singleShot(500, [=](){deleteLater();});

}