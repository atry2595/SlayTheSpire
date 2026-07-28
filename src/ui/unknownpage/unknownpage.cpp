#include "unknownpage.h"
#include "assetsManager/imagemanager.h"
#include "assetsManager/soundmanager.h"
#include "core/setting.h"
#include <QTimer>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "ui/topbar/combatsetting.h"
#include "ui/selectItem/selectcard.h"

UnknownPage::UnknownPage(UnknownManager manag, QWidget *parent, ironclad* plyr, combatEvent* eve)
    : QWidget{parent}
    , player(plyr)
    , eve(eve)
    , manager(manag)
{

    //----------------------------------------------------
    combatView = new QGraphicsView(this);
    combatScene = new QGraphicsScene(this);

    combatScene->setSceneRect(0, 0, 1600, 900);
    combatView->setScene(combatScene);

    combatView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setFrameShape(QFrame::NoFrame);
    combatView->setStyleSheet("background: #423E32;");

    combatView->setRenderHint(QPainter::Antialiasing, true);
    combatView->setRenderHint(QPainter::SmoothPixmapTransform, true);


    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(combatView);
    setLayout(layout);

    QMetaObject::invokeMethod(this, [this]() {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatio);
    }, Qt::QueuedConnection);

    //----------------------------------------------------

    bar = new CombatTopBar(eve, player, true);
    relic_bar = new RelicBar(eve, player->get_relic_list());

    combatScene->addItem(bar->getParent());
    combatScene->addItem(relic_bar->getParent());

    connect(eve, &combatEvent::settingOpen, this, &UnknownPage::open_setting);

    connect(eve, &combatEvent::relicRightButton, this, &UnknownPage::relic_right_click);

    connect(eve, &combatEvent::selectCard, this, &UnknownPage::createSelectCard);

    connect(eve, &combatEvent::barUpdate, this, &UnknownPage::update_bars);

    connect(eve, &combatEvent::card_added, this, &UnknownPage::add_card);

    initialSet();
}

UnknownPage::~UnknownPage() {

    if (bar) {
        delete bar;
        bar = nullptr;
    }
    if (relic_bar) {
        delete relic_bar;
        relic_bar = nullptr;
    }

    if (parent) delete parent;

    if (black_screen) delete black_screen;

    // Clean up combat view and scene
    if (combatScene) {
        // QGraphicsScene will clean up its items when deleted
        delete combatScene;
        combatScene = nullptr;
    }
    if (combatView) {
        delete combatView;
        combatView = nullptr;
    }

    player = nullptr;
    eve = nullptr;
}

void UnknownPage::Delete() {
    black_screen = new BaseItem(nullptr, {1700, 1000}, {-50, -50});
    black_screen->setBackColor(Qt::black);
    black_screen->setOpacity(0);
    black_screen->setZValue(200000);
    combatScene->addItem(black_screen);
    black_screen->fadeTo(1, 500);

    QTimer::singleShot(1000, [=](){
        this->deleteLater();
    });
}


void UnknownPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}

void UnknownPage::initialSet() {

    parent = new BaseItem(nullptr, {1200, 600}, {200, 200});
    parent->setBackColor(Qt::black);

    title = new TextItem(parent, {1100, 75}, {50, 10});
    title->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    title->setText(manager.unknown_name);
    QFont f;
    f.setFamily((setting::game_language == language::English) ? (Fonts::lotrance) : (Fonts::cinema));
    f.setBold(true);
    f.setPixelSize(45);
    title->setFont(f);
    title->setColor(Qt::yellow);

    image = new ImageItem(parent, {500, 500}, {25, 75});
    image->setPixmap(imageManager::instance().getUnknownImage(manager.unknown_ID));

    desc = new TextItem(parent, {625, 500}, {550, 75});
    desc->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    QFont fd;
    fd.setFamily((setting::game_language == language::English) ? (Fonts::Cascadia) : (Fonts::koodak));
    fd.setPixelSize(23);
    desc->setFont(fd);
    desc->setColor(Qt::white);

    combatScene->addItem(parent);
    parent->setOpacity(0);
    QTimer::singleShot(500, [=](){parent->fadeTo(1, 500);});

    eventUpdate();

}

void UnknownPage::eventUpdate() {

    QString btnStyle =
        "QPushButton{"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                               stop:0 #3c3a34,"
        "                               stop:1 #2a2823);"
        "   border: 2px solid #6a5a3a;"
        "   border-radius: 8px;"
        "   color: white;"
        "   font-size: 18px;"
        "   padding: 8px 20px;"
        "   text-align: left;"
        "}"
        "QPushButton:hover{"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                               stop:0 #544e3d,"
        "                               stop:1 #3c3a34);"
        "   border: 2px solid #c9a84c;"
        "}"
        "QPushButton:pressed{"
        "   background: qlineargradient(x1:0, y1:0, x2:0, y2:1,"
        "                               stop:0 #2a2823,"
        "                               stop:1 #3c3a34);"
        "   border: 2px solid #e5c46b;"
        "   padding-top: 10px;"
        "   padding-bottom: 6px;"
        "}"
        "QPushButton:disabled{"
        "   background: #1b1c1f;"
        "   color: #ccddaa;"
        "   border: 2px solid #3a3a3a;"
        "   color: #666666;"
        "}";

    QFont fd;
    fd.setFamily((setting::game_language == language::English) ? (Fonts::Cascadia) : (Fonts::koodak));
    fd.setPixelSize(23);

    if (manager.current_node == -1)  {
        emit eve->nextAction();
        return;
    }

    auto currentNode = manager.nodes[manager.current_node];
    currentNode.actions();
    bar->updateBar();
    combatScene->removeItem(relic_bar->getParent());
    delete relic_bar;
    relic_bar = new RelicBar(eve, player->get_relic_list());
    combatScene->addItem(relic_bar->getParent());
    desc->setText(currentNode.description);

    for (auto item : prxies) {
        item->deleteLater();
    }
    btns.clear();
    prxies.clear();


    int ln = currentNode.next_nodes.size();
    int yPos = 600 - 25;

    for (int i = ln - 1; i >= 0; --i) {
        QString btnText;
        bool canUse = true;
        int nxt = currentNode.next_nodes[i];

        if (nxt == -1) {
            btnText = tr("Leave");
        } else {
            btnText = manager.nodes[nxt].title;
            canUse = manager.nodes[nxt].canUse();
        }

        int btnHeight = ((int)(btnText.length() / 50 + 1)) * 40;

        yPos -= btnHeight;
        int currentBtnY = yPos;

        QPushButton* btn = new QPushButton();
        btn->setFixedSize(625, btnHeight);
        btn->setStyleSheet(btnStyle);
        btn->setFont(fd);
        btn->setText(btnText);
        btn->setEnabled(canUse);
        btn->installEventFilter(this);

        QGraphicsProxyWidget* prx = new QGraphicsProxyWidget(parent);
        prx->setWidget(btn);
        prx->setPos(550, currentBtnY);

        if (i > 0) {
            yPos -= 20;
        }

        btns.push_back(btn);
        prxies.push_back(prx);

        connect(btn, &QPushButton::clicked, this, [=](){
            manager.current_node = nxt;
            eventUpdate();
        });

    }
}

void UnknownPage::open_setting() {
    auto sc = new combatSetting(eve);
    combatScene->addItem(sc->getParent());
}


void UnknownPage::createSelectCard(std::vector<abstractCard*> cards) {
    auto sc = new selectCard(eve, cards);
    combatScene->addItem(sc->getParent());
    for (auto item : sc->getCards()){
        combatScene->addItem(item->getParent());
    }
}

bool UnknownPage::eventFilter(QObject* obj, QEvent* eve) {
    if (eve->type() == QEvent::Enter){
        soundManager::instance().playSoundEffect(SoundEffect::menuHover);
    }
    return QObject::eventFilter(obj, eve);
}


void UnknownPage::relic_right_click(abstractRelic* ent) {
    info_bar = new CombatInfoBar(ent);
    combatScene->addItem(info_bar->getParent());
    info_bar->Entrance();
}

void UnknownPage::update_bars() {
    bar->updateBar();
    combatScene->removeItem(relic_bar->getParent());
    delete relic_bar;
    relic_bar = new RelicBar(eve, player->get_relic_list());
    combatScene->addItem(relic_bar->getParent());
}

void UnknownPage::add_card(abstractCard* card) {
    abstractCardTemplate* item;

    switch (combat_data::selected_card_template) {
    case cardTemplates::ancient: {
        item = new CardTemplateUncommon(eve, card, {650, 200}, {300, 450}, 10);
        break;
    }
    case cardTemplates::common: {
        item = new CardTemplateCommon(eve, card, {650, 200}, {300, 450}, 10);
        break;
    }
    case cardTemplates::metallic: {
        item = new CardTemplateRare(eve, card, {650, 200}, {300, 450}, 10);
        break;
    }
    case cardTemplates::toxic_blossom: {
        item = new CardTemplateLegend(eve, card, {650, 200}, {300, 450}, 10);
        break;
    }
    }
    item->getParent()->setZValue(123456);
    item->getParent()->setCanHover(false);
    item->getParent()->setCanSelect(false);

    combatScene->addItem(item->getParent());
    QTimer::singleShot(1000, [=](){item->getParent()->moveTo({650, 1000}, 500, QEasingCurve::OutSine);});
    QTimer::singleShot(2000, [=](){ item->deleteLater();});
}