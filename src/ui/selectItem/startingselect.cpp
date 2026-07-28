#include "startingselect.h"
#include <QVBoxLayout>
#include <QResizeEvent>

startingSelect::startingSelect(QWidget *par, combatEvent* eve)
    : QWidget{par}
    , eve(eve)
{
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
    //------------------------------------------------------

    parent = new BaseItem(nullptr, {1650, 950});

    QString normal_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;color:white;}"
        "QPushButton:hover{background:transparent; color: white;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;
    QString selected_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;color:yellow;}"
        "QPushButton:hover{background:transparent; color: yellow;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;
    QFont f;
    f.setFamily((setting::game_language == language::English) ? (Fonts::Cascadia) : (Fonts::koodak));
    f.setPixelSize(24);

    auto c1 = new QPushButton();
    c1->setText(tr("classic ironclad"));
    c1->setStyleSheet(normal_css);
    c1->setFont(f);
    c1->installEventFilter(this);
    c1->setFixedSize(300, 50);
    auto pc1 = new QGraphicsProxyWidget(parent);
    pc1->setWidget(c1);
    pc1->setPos({50, 250});
    character_skin[skins::ironclad] = pc1;
    connect(c1, &QPushButton::clicked, this, [this](){updateChar(skins::ironclad);});

    auto c2 = new QPushButton();
    c2->setText(tr("armoured ironclad"));
    c2->setStyleSheet(normal_css);
    c2->setFont(f);
    c2->installEventFilter(this);
    c2->setFixedSize(300, 50);
    auto pc2 = new QGraphicsProxyWidget(parent);
    pc2->setWidget(c2);
    pc2->setPos({50, 350});
    character_skin[skins::armoured_ironclad] = pc2;
    connect(c2, &QPushButton::clicked, this, [this](){updateChar(skins::armoured_ironclad);});

    auto c3 = new QPushButton();
    c3->setText(tr("neon ironclad"));
    c3->setStyleSheet(normal_css);
    c3->setFont(f);
    c3->installEventFilter(this);
    c3->setFixedSize(300, 50);
    auto pc3 = new QGraphicsProxyWidget(parent);
    pc3->setWidget(c3);
    pc3->setPos({50, 450});
    character_skin[skins::neon_ironclad] = pc3;
    connect(c3, &QPushButton::clicked, this, [this](){updateChar(skins::neon_ironclad);});

    auto c4 = new QPushButton();
    c4->setText(tr("ancient ironclad"));
    c4->setStyleSheet(normal_css);
    c4->setFont(f);
    c4->installEventFilter(this);
    c4->setFixedSize(300, 50);
    auto pc4 = new QGraphicsProxyWidget(parent);
    pc4->setWidget(c4);
    pc4->setPos({50, 550});
    character_skin[skins::ancient_ironclad] = pc4;
    connect(c4, &QPushButton::clicked, this, [this](){updateChar(skins::ancient_ironclad);});

    auto c5 = new QPushButton();
    c5->setText(tr("cyberpunk ironclad"));
    c5->setStyleSheet(normal_css);
    c5->setFont(f);
    c5->installEventFilter(this);
    c5->setFixedSize(300, 50);
    auto pc5 = new QGraphicsProxyWidget(parent);
    pc5->setWidget(c5);
    pc5->setPos({50, 650});
    character_skin[skins::cyberpunk_ironclad] = pc5;
    connect(c5, &QPushButton::clicked, this, [this](){updateChar(skins::cyberpunk_ironclad);});


    auto t1 = new QPushButton();
    t1->setText(tr("common cards"));
    t1->setStyleSheet(normal_css);
    t1->setFont(f);
    t1->installEventFilter(this);
    t1->setFixedSize(300, 50);
    auto pt1 = new QGraphicsProxyWidget(parent);
    pt1->setWidget(t1);
    pt1->setPos({1300, 250});
    card_template[cardTemplates::common] = pt1;
    connect(t1, &QPushButton::clicked, this, [this](){updateCard(cardTemplates::common);});

    auto t2 = new QPushButton();
    t2->setText(tr("ancient cards"));
    t2->setStyleSheet(normal_css);
    t2->setFont(f);
    t2->installEventFilter(this);
    t2->setFixedSize(300, 50);
    auto pt2 = new QGraphicsProxyWidget(parent);
    pt2->setWidget(t2);
    pt2->setPos({1300, 350});
    card_template[cardTemplates::ancient] = pt2;
    connect(t2, &QPushButton::clicked, this, [this](){updateCard(cardTemplates::ancient);});

    auto t3 = new QPushButton();
    t3->setText(tr("metallic cards"));
    t3->setStyleSheet(normal_css);
    t3->setFont(f);
    t3->installEventFilter(this);
    t3->setFixedSize(300, 50);
    auto pt3 = new QGraphicsProxyWidget(parent);
    pt3->setWidget(t3);
    pt3->setPos({1300, 450});
    card_template[cardTemplates::metallic] = pt3;
    connect(t3, &QPushButton::clicked, this, [this](){updateCard(cardTemplates::metallic);});

    auto t4 = new QPushButton();
    t4->setText(tr("toxic blossom"));
    t4->setStyleSheet(normal_css);
    t4->setFont(f);
    t4->installEventFilter(this);
    t4->setFixedSize(300, 50);
    auto pt4 = new QGraphicsProxyWidget(parent);
    pt4->setWidget(t4);
    pt4->setPos({1300, 550});
    card_template[cardTemplates::toxic_blossom] = pt4;
    connect(t4, &QPushButton::clicked, this, [this](){updateCard(cardTemplates::toxic_blossom);});


    character = new ImageItem(parent, {400, 300}, {400, 300});
    card = new ImageItem(parent, {200, 300}, {1000, 300});

    f.setPixelSize(30);

    auto btn = new QPushButton();
    btn->setFont(f);
    btn->setStyleSheet(normal_css);
    btn->setText(tr("Start"));
    btn->setFixedSize(400, 100);
    btn->installEventFilter(this);
    start = new QGraphicsProxyWidget(parent);
    start->setWidget(btn);
    start->setPos(600, 750);
    combatScene->addItem(parent);
    connect(btn, &QPushButton::clicked, this, [=](){
        combat_data::selected_card_template = selected_card;
        combat_data::selected_character = selected_skin;
        emit eve->nextAction();
    });

    updateCard(cardTemplates::common);
    updateChar(skins::ironclad);
}

startingSelect::~startingSelect() {
    combatScene->removeItem(parent);
    if (parent) delete parent;
    delete combatScene;
    delete combatView;
}

void startingSelect::updateCard(cardTemplates tmp) {
    QString normal_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;color:white;}"
        "QPushButton:hover{background:transparent; color: white;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;
    QString selected_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;color:yellow;}"
        "QPushButton:hover{background:transparent; color: yellow;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;

    card_template[selected_card]->widget()->setStyleSheet(normal_css);
    selected_card = tmp;
    card_template[selected_card]->widget()->setStyleSheet(selected_css);

    card->setPixmap(imageManager::instance().getCardBack(selected_card));
}

void startingSelect::updateChar(skins sk) {
    QString normal_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;color:white;}"
        "QPushButton:hover{background:transparent; color: white;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;
    QString selected_css =
        "QPushButton{background:transparent;border:none;padding:0px;margin:0px;color:yellow;}"
        "QPushButton:hover{background:transparent; color: yellow;}"
        "QPushButton:pressed{background:transparent;}"
        "QPushButton:focus{border:none;outline:none;}"
        ;

    character_skin[selected_skin]->widget()->setStyleSheet(normal_css);
    selected_skin = sk;
    character_skin[selected_skin]->widget()->setStyleSheet(selected_css);

    character->setPixmap(imageManager::instance().getIroncladImage(selected_skin));
}

void startingSelect::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}

bool startingSelect::eventFilter(QObject* obj, QEvent* eve) {
    if (eve->type() == QEvent::Enter) {
        soundManager::instance().playSoundEffect(SoundEffect::menuHover);
    }
    return QObject::eventFilter(obj, eve);
}