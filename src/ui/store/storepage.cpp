#include "storepage.h"
#include "assetsManager/imagemanager.h"
#include "assetsManager/soundmanager.h"
#include "core/setting.h"
#include <QTimer>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "ui/selectItem/collectreward.h"
#include "ui/topbar/combatsetting.h"
#include "utils/RNG.h"
#include "items/relics/relicfactory.h"
#include "ui/selectItem/selectrelic.h"
#include "cards/cardfactory.h"

StorePage::StorePage(QWidget *parent, ChestType type, ironclad* plyr, combatEvent* eve)
    : QWidget{parent}
    , type(type)
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

    bar = new CombatTopBar(eve, player, true);
    relic_bar = new RelicBar(eve, player->get_relic_list());

    combatScene->addItem(bar->getParent());
    combatScene->addItem(relic_bar->getParent());
    //----------------------------------------------------
    connect(eve, &combatEvent::settingOpen, this, &StorePage::open_setting);

    initialSet();
}

StorePage::~StorePage() {

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

void StorePage::Delete() {
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


void StorePage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}

void StorePage::createCollectReward(combatReward* reward){
    QTimer::singleShot(1000, [=]() {
        auto cr = new collectReward(eve, reward, player);
        combatScene->addItem(cr->getParent());
    });
}



void StorePage::initialSet() {
    auto& rng = RNG::instance();

    parent = new BaseItem(nullptr , {1600,900} , {0,0});
    board = new BaseItem (parent , {1000,500} , {300 , 300});

    auto tmp = non_rare_cards ;

    std::vector<cardID> selected_non_rare = rng.sample(tmp, non_rare_card_number) ;

    for(auto item : selected_non_rare){
        auto created = CardFactory::CreateCard(item);
        cardprice[created] = rng.randint(50,80);

        switch(combat_data::selected_card_template) {
        case(cardTemplates::common): {
            auto* yechizi = CardTemplateCommon(eve , created, {0,0}, {0, 0}, 10);
            yechizi.getParent()->setCanHover(false);
            yechizi.getParent()->setCanSelect(false);
        }

        }

    }


    tmp = rare_cards;
    std::vector<cardID> selected_non_rare = rng.sample(tmp, non_rare_card_number) ;


}


void StorePage::open_setting() {
    auto sc = new combatSetting(eve);
    combatScene->addItem(sc->getParent());
}
