#include "selectcard.h"
#include "core/setting.h"
#include <QTimer>
#include "assetsManager/soundmanager.h"

selectCard::selectCard(combatEvent* eve, std::vector<abstractCard*> card_source)
    :event(eve)
{
    count = card_source.size();
    current_max = std::min(current_max, count);

    parent = new BaseItem(nullptr, {1650, 950}, {0, 0});
    parent->setBackColor(QColor::fromRgba(qRgba(0, 0, 30, 203)));
    parent->setZValue(13400);
    parent->setOpacity(0);

    overlay = new QPushButton();
    overlay->setFixedSize(1650, 950);
    overlay->setDisabled(true);
    overlay->setStyleSheet(
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;}"
        "QPushButton:hover{background:transparent;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        );
    overlay_proxy = new QGraphicsProxyWidget(parent);
    overlay_proxy->setWidget(overlay);
    overlay_proxy->setPos(0, 0);

    header = new TextItem(parent, {1000, 200}, {300, 50});
    header->setText(tr("Choose a Card:"));
    QFont f;
    f.setFamily(Fonts::Cascadia);
    f.setPixelSize(40);
    header->setFont(f);

    for (auto item : card_source) {
        abstractCardTemplate* ns;

        switch (combat_data::selected_card_template){
        case (cardTemplates::common):
            ns = new CardTemplateCommon(event, item, {1650, 950}, {200, 300}, 13456);;
            break;

        case (cardTemplates::metallic):
            ns = new CardTemplateRare(event, item, {1650, 950}, {200, 300}, 13456);;
            break;

        case (cardTemplates::ancient):
            ns = new CardTemplateUncommon(event, item, {1650, 950}, {200, 300}, 13456);;
            break;

        case (cardTemplates::toxic_blossom):
            ns = new CardTemplateLegend(event, item, {1650, 950}, {200, 300}, 13456);;
            break;
        }
        ns->getParent()->setCanHover(false);
        ns->getParent()->setCanSelect(false);
        ns->getParent()->setZValue(13450);
        ns->getParent()->setOpacity(0);
        ns->getParent()->fadeTo(1, 500, QEasingCurve::OutSine);
        cards.push_back(ns);
    }

    next_button = new QPushButton();
    next_button->setFixedSize(100, 100);
    next_button->setIcon(QIcon(":/icon/right_button.png"));
    next_button->setIconSize(QSize(100, 100));
    next_button->setShortcut(Qt::Key_Right);
    next_button->setDisabled(5 >= count);
    next_button->setStyleSheet(
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;}"
        "QPushButton:hover{background:transparent;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        );
    connect(next_button, &QPushButton::clicked, this, &selectCard::nextCards);

    pre_button = new QPushButton();
    pre_button->setFixedSize(100, 100);
    pre_button->setIcon(QIcon(":/icon/left_button.png"));
    pre_button->setIconSize(QSize(100, 100));
    pre_button->setShortcut(Qt::Key_Left);
    pre_button->setDisabled(true);
    pre_button->setStyleSheet(
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;}"
        "QPushButton:hover{background:transparent;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        );
    connect(pre_button, &QPushButton::clicked, this, &selectCard::preCards);


    pre_proxy = new QGraphicsProxyWidget(parent);
    pre_proxy->setWidget(pre_button);
    pre_proxy->setPos(600, 750);

    next_proxy = new QGraphicsProxyWidget(parent);
    next_proxy->setWidget(next_button);
    next_proxy->setPos(900, 750);

    parent->fadeTo(1, 500, QEasingCurve::OutSine);
    connect(eve, &combatEvent::cardPressed, this, &selectCard::cardSelected);

    execute();
}

void selectCard::execute() {
    current_min = std::max(current_min, 0);
    current_max = std::min(current_max, count - 1);

    for (int i = 0; i < count; i++){

        qreal x = 100 + 302 * (i - current_min);

        cards[i]->getParent()->setPos(x, 300);

    }
}

void selectCard::nextCards() {
    if (current_max < count - 1) {
        current_max++;
        current_min++;

        if (current_max == count - 1){
            next_button->setDisabled(true);
        }
        if (current_min == 1) {
            pre_button->setDisabled(false);
        }
        execute();
    }
}

void selectCard::preCards() {
    if (current_min > 0) {
        current_max--;
        current_min--;

        if (current_max == count - 2){
            next_button->setDisabled(false);
        }
        if (current_min == 0) {
            pre_button->setDisabled(true);
        }
        execute();
    }
}

void selectCard::cardSelected(CardParent* card) {

    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    emit event->cardSelected(card->getSource());
    for (auto item : cards){
        item->getParent()->fadeTo(0, 500, QEasingCurve::OutSine);
        QTimer::singleShot(500, [=](){delete item->getParent();});
    }
    parent->fadeTo(0, 500, QEasingCurve::OutSine);
    QTimer::singleShot(500, [=](){delete parent;});
    QTimer::singleShot(500, [=](){deleteLater();});

}