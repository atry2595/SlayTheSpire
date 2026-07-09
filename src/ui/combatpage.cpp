#include "combatpage.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QSequentialAnimationGroup>
#include "imageitem.h"
#include "cards/cardfactory.h"
#include "cards/cardtemplatecommon.h"
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



    ImageItem* bg = new ImageItem(nullptr, {1620, 920}, {-10, -10});
    bg->setPixmap(QPixmap(":/image/scene/map2_epic.jpg"));
    bg->setZValue(-1000);
    combatScene->addItem(bg);

    ImageItem* ir = new ImageItem(nullptr, {400, 275}, {155, 370});
    ir->setPixmap(QPixmap(":/image/characters/ironclad1.png"));
    ir->setZValue(0);

    auto u = ir->createGeometryAnimation({155, 370 -14, 400, 275 + 14}, 750, QEasingCurve::InSine);
    auto f = ir->createGeometryAnimation({155, 370, 400, 275}, 750, QEasingCurve::OutSine);

    auto* gr = new QSequentialAnimationGroup();
    gr->addAnimation(u);
    gr->addAnimation(f);
    gr->setLoopCount(-1);
    gr->start();
    combatScene->addItem(ir);



    abstractCard* c0 = CardFactory::createCard(cardID::reaper);
    abstractCard* c1 = CardFactory::createCard(cardID::perfected_strike);
    abstractCard* c2 = CardFactory::createCard(cardID::whirlwind);
    c2->upgrade();
    abstractCard* c3 = CardFactory::createCard(cardID::bludgeon);
    c3->upgrade();
    abstractCard* c4 = CardFactory::createCard(cardID::true_grit);
    c4->set_lock(true);

    CardTemplateCommon* card0 = new CardTemplateCommon(c0, {700 - 300, 700}, {200, 300}, 0);
    CardTemplateCommon* card1 = new CardTemplateCommon(c1, {700 - 150, 700}, {200, 300}, 1000);
    CardTemplateCommon* card2 = new CardTemplateCommon(c2, {700, 700}, {200, 300}, 2000);
    CardTemplateCommon* card3 = new CardTemplateCommon(c3, {700 + 150, 700}, {200, 300}, 3000);
    CardTemplateCommon* card4 = new CardTemplateCommon(c4, {700 + 300, 700}, {200, 300}, 4000);


    combatScene->addItem(card0->getParent());
    combatScene->addItem(card1->getParent());
    combatScene->addItem(card2->getParent());
    combatScene->addItem(card3->getParent());
    combatScene->addItem(card4->getParent());





}

void CombatPage::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    if (combatView && combatScene) {
        combatView->fitInView(combatScene->sceneRect(), Qt::KeepAspectRatioByExpanding);
    }
}