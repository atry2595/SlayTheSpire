#include "selectpotion.h"
#include "core/setting.h"
#include <QTimer>
#include "assetsManager/imagemanager.h"
#include "assetsManager/soundmanager.h"


selectPotion::selectPotion(combatEvent* eve, std::vector<abstractPotion*> potion_source)
    :event(eve)
    ,potions(potion_source)
{

    QString blank_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;}"
        "QPushButton:hover{background:transparent;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;

    parent = new BaseItem(nullptr, {1650, 950}, {0, 0});
    parent->setBackColor(QColor::fromRgba(qRgba(0, 0, 30, 220)));
    parent->setZValue(13500);
    parent->setOpacity(0);

    overlay = new QPushButton();
    overlay->setFixedSize(1650, 950);
    overlay->setDisabled(true);
    overlay->setStyleSheet(blank_css);
    overlay_proxy = new QGraphicsProxyWidget(parent);
    overlay_proxy->setWidget(overlay);
    overlay_proxy->setPos(0, 0);

    header = new TextItem(parent, {1000, 200}, {300, 50});
    header->setText(tr("Remove a potion:"));
    QFont f;
    f.setFamily(Fonts::Cascadia);
    f.setPixelSize(40);
    header->setFont(f);

    for (auto item : potions) {
        auto par = new BaseItem(parent, {200, 300});
        auto img = new ImageItem(par, {150, 150}, {25, 0});
        img->setPixmap(imageManager::instance().getPotionIcon(item->get_ID()));

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
        connect(btn, &QPushButton::clicked, this, [=]() {potionSelected(item);});
        auto prx = new QGraphicsProxyWidget(par);
        prx->setWidget(btn);
        potion_parent.push_back(par);
    }

    execute();
}

void selectPotion::execute() {

    for (int i = 0; i < 4; i++){

        qreal x = 250 + 302 * i;

        potion_parent[i]->setPos(x, 300);

    }

    parent->fadeTo(1, 500);
}

void selectPotion::potionSelected(abstractPotion* pt) {

    if (selected) return;
    selected = true;

    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    emit event->potionSelected(pt);
    parent->fadeTo(0, 500, QEasingCurve::OutSine);
    QTimer::singleShot(500, [=](){delete parent;});
    QTimer::singleShot(500, [=](){deleteLater();});

}