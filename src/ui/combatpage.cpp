#include "combatpage.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QSequentialAnimationGroup>
#include "imageitem.h"
#include "cards/cardfactory.h"
#include "ui/cards/cardtemplatecommon.h"
#include "ui/cards/cardtemplateuncommon.h"
#include "ui/cards/cardtemplaterare.h"
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



    abstractCard* c0 = CardFactory::createCard(cardID::bash);
    c0->set_lock(true);
    abstractCard* c1 = CardFactory::createCard(cardID::immolate);
    abstractCard* c2 = CardFactory::createCard(cardID::demon_form);
    c2->upgrade();
    abstractCard* c3 = CardFactory::createCard(cardID::JAX);
    c3->upgrade();
    abstractCard* c4 = CardFactory::createCard(cardID::pommel_strike);

    CardTemplateRare* card0 = new CardTemplateRare(c0, {700 - 300, 700}, {200, 300}, 0);
    CardTemplateRare* card1 = new CardTemplateRare(c1, {700 - 150, 700}, {200, 300}, 10);
    CardTemplateRare* card2 = new CardTemplateRare(c2, {700, 700}, {200, 300}, 20);
    CardTemplateRare* card3 = new CardTemplateRare(c3, {700 + 150, 700}, {200, 300}, 30);
    CardTemplateRare* card4 = new CardTemplateRare(c4, {700 + 300, 700}, {200, 300}, 40);


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