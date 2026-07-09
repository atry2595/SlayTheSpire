#include "combatpage.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QSequentialAnimationGroup>
#include "imageitem.h"
#include "baseitem.h"
#include "textitem.h"
#include <QParallelAnimationGroup>

CombatPage::CombatPage(QWidget *parent)
    : QWidget{parent}
{
    combatView = new QGraphicsView(this);
    combatScene = new QGraphicsScene(this);

    combatScene->setSceneRect(0, 0, 1600, 900);
    combatView->setScene(combatScene);

    combatView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    combatView->setFrameShape(QFrame::NoFrame);
    combatView->setStyleSheet("background: red;");

    combatView->setRenderHint(QPainter::Antialiasing);





    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    layout->addWidget(combatView);
    setLayout(layout);

    QMetaObject::invokeMethod(this, [this]() {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatio);
    }, Qt::QueuedConnection);

    std::vector<QString> v {
        ":/image/cards/curse/curse_of_bell.png",
        ":/image/cards/skill/defend.png",
        ":/image/cards/attack/bash.png",
        ":/image/cards/skill/defend.png",
        ":/image/cards/skill/exhume.png",
        ":/image/cards/attack/strike.png",
        ":/image/cards/curse/pain.png",
        ":/image/cards/attack/twin_strike.png",
        ":/image/cards/attack/strike.png",
        ":/image/cards/attack/hemokinesis.png",
        ":/image/cards/skill/entrench.png",
        ":/image/cards/attack/blood_for_blood.png",
    };

    ImageItem* bg = new ImageItem(nullptr, {1620, 920}, {-10, -10});
    bg->setPixmap(QPixmap(":/image/scene/map1_normal.jpg"));
    bg->setZValue(-1000);
    combatScene->addItem(bg);

    ImageItem* ir = new ImageItem(nullptr, {400, 275}, {70, 187});
    ir->setPixmap(QPixmap(":/image/characters/ironclad4.png"));
    ir->setZValue(0);

    auto u = ir->createGeometryAnimation({70, 187 - 3.5, 400, 275 + 5}, 1500, QEasingCurve::InSine);
    auto f = ir->createGeometryAnimation({70, 187, 400, 275}, 1500, QEasingCurve::OutSine);

    auto* gr = new QSequentialAnimationGroup();
    gr->addAnimation(u);
    gr->addAnimation(f);
    gr->setLoopCount(-1);
    gr->start();





    combatScene->addItem(ir);


    for (int i = 0; i<11; i++) {
        BaseItem* valed = new BaseItem();
        valed->setPos(700 + 140 * (i - 5), 700);
        valed->setMovable();
        combatScene->addItem(valed);

        ImageItem* card = new ImageItem(valed, {200, 300}, {0, 0});
        card->setPixmap(QPixmap(":/card/frame/frame2.png"));
        card->setZValue(2 + i*10);


        ImageItem* img = new ImageItem(valed, {146, 218}, QPointF(27, 54));
        img->update();
        img->setPixmap(QPixmap(v[i]));
        img->setZValue(1 + i*10);
    }

}

void CombatPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}