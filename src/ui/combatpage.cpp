#include "combatpage.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QSequentialAnimationGroup>
#include "imageitem.h"
#include "cards/cardfactory.h"
#include "ui/cards/cardtemplatecommon.h"
#include "ui/cards/cardtemplateuncommon.h"
#include "ui/cards/cardtemplaterare.h"
#include "ui/cards/cardtemplatelegend.h"
#include "ui/entities/ironcladitem.h"
#include "items//powers/powerfactory.h"
#include "entity/ironclad.h"
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

    // ImageItem* ir = new ImageItem(nullptr, {400, 275}, {155, 370});
    // ir->setPixmap(QPixmap(":/image/characters/ironclad5.png"));
    // ir->setZValue(0);


    auto plyr = new ironclad(nullptr);
    auto pwr = PowerFactory::createPower(powerID::strength, plyr, 5);
    game_action acts(nullptr);
    plyr->add_power(acts, pwr);

    pwr = PowerFactory::createPower(powerID::strength, plyr, -3);
    plyr->add_power(acts, pwr);

    pwr = PowerFactory::createPower(powerID::dexterity, plyr, -3);
    plyr->add_power(acts, pwr);

    pwr = PowerFactory::createPower(powerID::berserk, plyr, 1);
    plyr->add_power(acts, pwr);

    auto plyr_item = new IroncladItem(plyr, {170, 400}, 100);
    combatScene->addItem(plyr_item->getParent());
    plyr_item->getParent()->activeAttackAnimation();


    // auto u = ir->createGeometryAnimation({155, 370 -14, 400, 275 + 14}, 750, QEasingCurve::InSine);
    // auto f = ir->createGeometryAnimation({155, 370, 400, 275}, 750, QEasingCurve::OutSine);

    // auto* gr = new QSequentialAnimationGroup();
    // gr->addAnimation(u);
    // gr->addAnimation(f);
    // gr->setLoopCount(-1);
    // gr->start();
    // combatScene->addItem(ir);



    abstractCard* c0 = CardFactory::createCard(cardID::bash);
    c0->set_lock(true);
    abstractCard* c1 = CardFactory::createCard(cardID::demon_form);
    abstractCard* c2 = CardFactory::createCard(cardID::reaper);
    c2->upgrade();
    abstractCard* c3 = CardFactory::createCard(cardID::heavy_blade);
    c3->upgrade();
    abstractCard* c4 = CardFactory::createCard(cardID::feel_no_pain);

    CardTemplateLegend* card0 = new CardTemplateLegend(c0, {700 - 300, 700}, {200, 300}, 0);
    CardTemplateLegend* card1 = new CardTemplateLegend(c1, {700 - 150, 700}, {200, 300}, 10);
    CardTemplateLegend* card2 = new CardTemplateLegend(c2, {700, 700}, {200, 300}, 20);
    CardTemplateLegend* card3 = new CardTemplateLegend(c3, {700 + 150, 700}, {200, 300}, 30);
    CardTemplateLegend* card4 = new CardTemplateLegend(c4, {700 + 300, 700}, {200, 300}, 40);


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