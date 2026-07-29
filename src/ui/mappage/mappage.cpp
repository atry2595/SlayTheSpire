#include "MapPage.h"
#include "assetsManager/imagemanager.h"
#include "assetsManager/soundmanager.h"
#include "core/setting.h"
#include <QTimer>
#include <QVBoxLayout>
#include <QResizeEvent>
#include "ui/topbar/combatsetting.h"
#include "utils/RNG.h"
#include "ui/mappage/mapItems.h"
#include "ui/mappage/sketchline.h"

MapPage::MapPage(QWidget *parent, ironclad* plyr, combatEvent* eve)
    : QWidget{parent}
    , player(plyr)
    , eve(eve)
{

    auto mng = imageManager::instance();
    auto sound = soundManager::instance();
    int floor = 1;

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

    connect(eve, &combatEvent::settingOpen, this, &MapPage::open_setting);

    connect(eve, &combatEvent::relicRightButton, this, &MapPage::relic_right_click);

    generateNewMap();
    initialSet();
}

MapPage::~MapPage() {

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

void MapPage::Delete() {
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


void MapPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}

void MapPage::initialSet() {
    QString blank_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;}"
        "QPushButton:hover{background:transparent;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;

    parent = new BaseItem(nullptr);

    scroll = new ScrollSection(parent, {1600, 3600}, {0, 0}, 3600 - 1000 , 3600 - 900, 0);

    auto* back = new ImageItem(scroll, {1300, 3375}, {150, 150});
    back->setPixmap(imageManager::instance().getMapImage("map"));

    for (auto item : combat_data::combat_map.lines) {
        new SketchLine(item.origin, item.target, scroll);
    }

    btnToRoom.clear();
    btns.clear();

    for (auto item : combat_data::combat_map.rooms) {
        auto* ps = new QPushButton();
        ps->setFixedSize(50, 50);
        ps->setStyleSheet(blank_css);
        ps->setIcon(QIcon(imageManager::instance().getMapImage(item.first.type)));
        ps->setIconSize({50, 50});
        ps->installEventFilter(this);

        auto* prx = new QGraphicsProxyWidget(scroll);
        prx->setWidget(ps);
        prx->setTransformOriginPoint(25, 25);
        prx->setPos(item.second.x, item.second.y);
        prx->setOpacity(0.65);

        btns[ps] = prx;
        btnToRoom[ps] = item.first;

        connect(ps, &QPushButton::clicked, this, [this, ps]() {
            onRoomClicked(ps);
        });
    }

    auto* legend = new ImageItem(parent, {250, 350}, {1600 - 275, 450 - 150});
    legend->setPixmap(imageManager::instance().getMapImage("legend"));

    QFont f;
    f.setFamily((setting::game_language == language::English)?(Fonts::Cascadia):(Fonts::koodak));
    f.setPixelSize(20);

    TextItem* monster = new TextItem(legend, {250, 50}, {0, 60 - 10});
    monster->setText(tr("Monster"));
    monster->setFont(f);
    ImageItem* mons_img = new ImageItem(monster, {40, 40}, {20, 5});
    mons_img->setPixmap(imageManager::instance().getMapImage(RoomType::MONSTER));

    TextItem* elite = new TextItem(legend, {250, 50}, {0, 100 - 10});
    elite->setText(tr("Elite"));
    elite->setFont(f);
    ImageItem* elite_img = new ImageItem(elite, {40, 40}, {20, 5});
    elite_img->setPixmap(imageManager::instance().getMapImage(RoomType::ELITE));

    TextItem* unknown = new TextItem(legend, {250, 50}, {0, 140 - 10});
    unknown->setText(tr("Unknown"));
    unknown->setFont(f);
    ImageItem* unk_img = new ImageItem(unknown, {40, 40}, {20, 5});
    unk_img->setPixmap(imageManager::instance().getMapImage(RoomType::UNKNOWN));

    TextItem* campfire = new TextItem(legend, {250, 50}, {0, 180 - 10});
    campfire->setText(tr("Rest"));
    campfire->setFont(f);
    ImageItem* rest_img = new ImageItem(campfire, {40, 40}, {20, 5});
    rest_img->setPixmap(imageManager::instance().getMapImage(RoomType::REST));

    TextItem* treasure = new TextItem(legend, {250, 50}, {0, 220 - 10});
    treasure->setText(tr("Treasure"));
    treasure->setFont(f);
    ImageItem* tre_img = new ImageItem(treasure, {40, 40}, {20, 5});
    tre_img->setPixmap(imageManager::instance().getMapImage(RoomType::TREASURE));

    TextItem* merchant = new TextItem(legend, {250, 50}, {0, 260 - 10});
    merchant->setText(tr("Shop"));
    merchant->setFont(f);
    ImageItem* mer_img = new ImageItem(merchant, {40, 40}, {20, 5});
    mer_img->setPixmap(imageManager::instance().getMapImage(RoomType::MERCHANT));

    TextItem* legend_title = new TextItem(legend, {250, 50}, {0, 0});
    legend_title->setText(tr("Legend"));
    legend_title->setFont(f);


    combatScene->addItem(scroll);
    combatScene->addItem(legend);

    refreshMapVisuals();
}


void MapPage::open_setting() {
    auto sc = new combatSetting(eve);
    combatScene->addItem(sc->getParent());
}


void MapPage::generateNewMap() {
    auto* mp = new Map();
    mp->generate();

    std::map<Room, RoomItem> rooms;

    for (int flr = 0; flr < mp->TOTAL_FLOORS; flr++){
        for (Room item : mp->getRoomsOnFloor(flr)) {
            qreal x = 150 + 50 + item.col * 150 + RNG::instance().randint(0, 75);
            qreal y = 3400 - 75 - item.floor * 200 + RNG::instance().randint(0, 70);
            RoomItem rmi;
            rmi.source = item;
            rmi.x = x;
            rmi.y = y;

            rooms[item] = rmi;
        }
    }

    std::vector<LineItem> lines;

    for (auto item : rooms) {
        int room_x = item.second.x + 25;
        int room_y = item.second.y + 7;

        QPointF ori(room_x, room_y);

        int room_col = item.first.col;
        int room_floor = item.first.floor;

        for (auto child : mp->getNextRooms(room_floor, room_col)) {
            int child_x = rooms[child].x + 25;
            int child_y = rooms[child].y + 43;
            QPointF des(child_x, child_y);
            LineItem line;
            line.origin = ori;
            line.target = des;
            lines.push_back(line);
        }
    }

    combatMap m;
    m.map = mp;
    m.rooms = rooms;
    m.lines = lines;
    m.currentFloor = -1;
    m.currentCol = -1;

    combat_data::combat_map = m;
}

bool MapPage::eventFilter(QObject* obj, QEvent* eve) {
    if (eve->type() == QEvent::Enter){
        soundManager::instance().playSoundEffect(SoundEffect::mapHover);
        auto* o = dynamic_cast<QPushButton*>(obj);
        if (o) {
            if (btns.contains(o)) {
                btns[o]->setOpacity(1);
                btns[o]->setScale(1.5);
            }
        }
    }
    if (eve->type() == QEvent::Leave){
        auto* o = dynamic_cast<QPushButton*>(obj);
        refreshMapVisuals();
    }
    return QObject::eventFilter(obj, eve);
}

void MapPage::refreshMapVisuals() {
    auto& cm = combat_data::combat_map;

    QList<Room> selectableRooms;

    if (cm.currentCol == -1) {
        for (auto& item : cm.rooms) {
            if (item.first.floor == 0 && item.first.active) {
                selectableRooms.append(item.first);
            }
        }
    }

    else if (cm.map->isFinished()) {
    }

    else {
        selectableRooms = cm.map->getNextRooms(cm.currentFloor, cm.currentCol);
    }

    for (auto it = btnToRoom.begin(); it != btnToRoom.end(); ++it) {
        QPushButton* btn = it.key();
        Room room = it.value();

        if (!btns.contains(btn)) continue;
        QGraphicsProxyWidget* prx = btns[btn];

        const Room& realRoom = cm.map->getRoom(room.floor, room.col);

        bool isCurrent = (realRoom.floor == cm.currentFloor && realRoom.col == cm.currentCol);

        bool isSelectable = false;
        for (const Room& r : selectableRooms) {
            if (r.floor == realRoom.floor && r.col == realRoom.col) {
                isSelectable = true;
                break;
            }
        }

        bool isVisited = realRoom.visited;

        if (isSelectable) {
            prx->setOpacity(1.0);
            prx->setScale(1.2);
            btn->setEnabled(true);
        }
        else if (isVisited) {
            prx->setOpacity(0.8);
            prx->setScale(1.5);
            btn->setEnabled(false);
        }
        else {
            prx->setOpacity(0.4);
            prx->setScale(1.0);
            btn->setEnabled(false);
        }
    }
}

void MapPage::onRoomClicked(QPushButton* btn) {
    soundManager::instance().playSoundEffect(SoundEffect::mapSelect);
    if (!btnToRoom.contains(btn)) return;

    Room clickedRoom = btnToRoom[btn];
    auto& cm = combat_data::combat_map;

    if (cm.currentFloor >= 0 && cm.currentCol >= 0) {
        cm.map->getRoom(cm.currentFloor, cm.currentCol).visited = true;
    }

    if (cm.currentCol == -1) {
        cm.map->enterStartingRoom(clickedRoom.col);
    }

    else {
        cm.map->moveTo(clickedRoom.col);
    }

    cm.currentFloor = cm.map->getCurrentFloor();
    cm.currentCol = cm.map->getCurrentColumn();

    combat_data::floor = cm.currentFloor;
    combat_data::room_type = clickedRoom.type;

    emit eve->nextAction();

    QTimer::singleShot(500, [=](){refreshMapVisuals();});
}

void MapPage::relic_right_click(abstractRelic* ent) {
    info_bar = new CombatInfoBar(ent);
    combatScene->addItem(info_bar->getParent());
    info_bar->Entrance();
}