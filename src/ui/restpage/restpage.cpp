#include "restpage.h"
#include "assetsManager/imagemanager.h"
#include "assetsManager/soundmanager.h"
#include "core/setting.h"
#include <QTimer>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "ui/topbar/combatsetting.h"
#include "ui/selectItem/selectcard.h"

RestPage::RestPage(QWidget *parent, ironclad* plyr, combatEvent* eve)
    : QWidget{parent}
    , player(plyr)
    , eve(eve)
{

    auto mng = imageManager::instance();
    auto sound = soundManager::instance();


    //----------------------------------------------------
    combatView = new QGraphicsView(this);
    combatScene = new QGraphicsScene(this);

    combatScene->setSceneRect(0, 0, 1600, 900);
    combatView->setScene(combatScene);

    combatView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setFrameShape(QFrame::NoFrame);
    combatView->setStyleSheet("background: black;");

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
    if (combat_data::act == 1) soundManager::instance().playBackMusic(BgMusic::act1_rest);
    if (combat_data::act == 2) soundManager::instance().playBackMusic(BgMusic::act2_rest);

    ImageItem* bg = new ImageItem(nullptr, {1632, 918}, {-16, -9});
    bg->setPixmap(mng.getBackroundImage());
    bg->setZValue(0);
    combatScene->addItem(bg);

    bar = new CombatTopBar(eve, player, true);
    relic_bar = new RelicBar(eve, player->get_relic_list());

    combatScene->addItem(bar->getParent());
    combatScene->addItem(relic_bar->getParent());
    //----------------------------------------------------

    connect(eve, &combatEvent::settingOpen, this, &RestPage::open_setting);

    connect(eve, &combatEvent::relicRightButton, this, &RestPage::relic_right_click);

    connect(eve, &combatEvent::selectCard, this, &RestPage::createSelectCard);

    initialSet();
}

RestPage::~RestPage() {

    if (bar) {
        delete bar;
        bar = nullptr;
    }
    if (relic_bar) {
        delete relic_bar;
        relic_bar = nullptr;
    }

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

void RestPage::Delete() {
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


void RestPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}


void RestPage::initialSet() {
    if (!can_rest && !can_lift && !can_smith) {
        emit eve->nextAction();
    }

    QString blank_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;text-align:left;}"
        "QPushButton:hover{background:transparent; color: #00CCFF;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;

    parent = new BaseItem(nullptr, {1650, 950});
    parent->setOpacity(0);
    combatScene->addItem(parent);
    QTimer::singleShot(500, [=](){parent->fadeTo(1, 500);});

    header = new TextItem(parent, {800, 100}, {400, 100});
    header->setText(tr("You find Sacred Well"));
    QFont f;
    f.setFamily((setting::game_language == language::English) ? (Fonts::forte) : (Fonts::cinema));
    f.setPixelSize(70);
    header->setFont(f);
    header->setColor(QColor::fromRgb(0, 200, 255));


    QFont bf;
    bf.setFamily((setting::game_language == language::English) ? (Fonts::Cascadia) : (Fonts::koodak));
    bf.setPixelSize(40);
    qreal y = 250;

    if (can_rest) {
        rest_button = new QPushButton();
        rest_button->setFont(bf);
        rest_button->setText(tr("Drink Water(30% HP)"));
        rest_button->setFixedSize({600, 60});
        rest_button->installEventFilter(this);
        rest_button->setStyleSheet(blank_css);

        rest_proxy = new QGraphicsProxyWidget(parent);
        rest_proxy->setWidget(rest_button);
        rest_proxy->setPos({200, y});
        y += 125;

        connect(rest_button, &QPushButton::clicked, this, [=](){
            if (can_lift) lift_button->setDisabled(true);
            if (can_smith) smith_button->setDisabled(true);
            if (can_rest) rest_button->setDisabled(true);
            soundManager::instance().playSoundEffect(SoundEffect::drinkPotion);
            healInfo h;
            h.owner = player;
            h.value = player->get_max_hp() * 0.3;
            emit eve->campRest(player);
            emit eve->nextAction();
        });
    }

    if (can_smith) {
        smith_button = new QPushButton();
        smith_button->setFont(bf);
        smith_button->setText(tr("Bless Card(Smith)"));
        smith_button->setFixedSize({600, 60});
        smith_button->installEventFilter(this);
        smith_button->setStyleSheet(blank_css);

        smith_proxy = new QGraphicsProxyWidget(parent);
        smith_proxy->setWidget(smith_button);
        smith_proxy->setPos({200, y});
        y += 125;

        connect(smith_button, &QPushButton::clicked, this, [=](){
            if (can_lift) lift_button->setDisabled(true);
            if (can_smith) smith_button->setDisabled(true);
            if (can_rest) rest_button->setDisabled(true);
            soundManager::instance().playSoundEffect(SoundEffect::drinkPotion);

            std::vector<abstractCard*> pool;
            for (auto item : player->get_deck()) {
                if (item->get_card_type() != CardType::curse && item->get_upgraded() == false) {
                    pool.push_back(item);
                }
            }

            emit eve->selectCard(pool);
            connect(eve, &combatEvent::cardSelected, this, [=](abstractCard* card){
                card->base_upgrade();
                soundManager::instance().playSoundEffect(SoundEffect::smith);
                emit eve->campSmith(player);
                emit eve->nextAction();
            });
        });
    }

    if (can_lift) {
        lift_button = new QPushButton();
        lift_button->setFont(bf);
        lift_button->setText(tr("Bless Girya(lift)"));
        lift_button->setFixedSize({600, 60});
        lift_button->installEventFilter(this);
        lift_button->setStyleSheet(blank_css);

        lift_proxy = new QGraphicsProxyWidget(parent);
        lift_proxy->setWidget(lift_button);
        lift_proxy->setPos({200, y});

        connect(lift_button, &QPushButton::clicked, this, [=](){
            if (can_lift) lift_button->setDisabled(true);
            if (can_smith) smith_button->setDisabled(true);
            if (can_rest) rest_button->setDisabled(true);

            soundManager::instance().playSoundEffect(SoundEffect::drinkPotion);
            emit eve->lift(player);
            emit eve->nextAction();
        });
    }


}


void RestPage::open_setting() {
    auto sc = new combatSetting(eve);
    combatScene->addItem(sc->getParent());
}

bool RestPage::eventFilter(QObject* obj, QEvent* eve) {
    if (eve->type() == QEvent::Enter){
        soundManager::instance().playSoundEffect(SoundEffect::menuHover);
    }
    return QObject::eventFilter(obj, eve);
}


void RestPage::relic_right_click(abstractRelic* ent) {
    info_bar = new CombatInfoBar(ent);
    combatScene->addItem(info_bar->getParent());
    info_bar->Entrance();
}


void RestPage::createSelectCard(std::vector<abstractCard*> cards) {
    auto sc = new selectCard(eve, cards);
    combatScene->addItem(sc->getParent());
    for (auto item : sc->getCards()){
        combatScene->addItem(item->getParent());
    }
}