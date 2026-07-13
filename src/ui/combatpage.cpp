#include "combatpage.h"
#include <QVBoxLayout>
#include <QResizeEvent>
#include <QSequentialAnimationGroup>
#include "imageitem.h"
#include "cards/cardfactory.h"
#include "ui/cards/cardtemplatecommon.h"
#include "ui/entities/ironcladitem.h"
#include "items//powers/powerfactory.h"
#include "entity/ironclad.h"
#include <QParallelAnimationGroup>
#include "ui/entities/blueslaveritem.h"
#include "entity/blue_slaver.h"
#include "ui/entities/EnemyItem.h"
#include "entity/hexaghost.h"
#include "entity/medium_slime.h"
#include "entity/book_of_stabbing.h"
#include "entity/red_louse.h"
#include "ui/entities/enemyitem.h"
#include "entity/red_slaver.h"
#include "entity/spheric_guardian.h"

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

    pwr = PowerFactory::createPower(powerID::demon_form, plyr, 3);
    plyr->add_power(acts, pwr);

    pwr = PowerFactory::createPower(powerID::dexterity, plyr, -3);
    plyr->add_power(acts, pwr);

    pwr = PowerFactory::createPower(powerID::entangled, plyr, 1);
    plyr->add_power(acts, pwr);

    auto plyr_item = new IroncladItem(plyr, {170, 360}, 100);
    combatScene->addItem(plyr_item->getParent());
    plyr_item->getParent()->activeAttackAnimation();

    auto enm = spheric_guardian::create(acts);
    pwr = PowerFactory::createPower(powerID::strength, enm, 3);
    enm->add_power(acts, pwr);

    pwr = PowerFactory::createPower(powerID::vulnerable, enm, 2);
    enm->add_power(acts, pwr);

    auto enm_item = new EnemyItem(enm, {1600 - 600, 360 - 100}, 100);
    combatScene->addItem(enm_item->getParent());
    enm_item->getParent()->activeAttackAnimation();


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

    CardTemplateCommon* card0 = new CardTemplateCommon(c0, {700 - 300, 700}, {200, 300}, 0);
    CardTemplateCommon* card1 = new CardTemplateCommon(c1, {700 - 150, 700}, {200, 300}, 10);
    CardTemplateCommon* card2 = new CardTemplateCommon(c2, {700, 700}, {200, 300}, 20);
    CardTemplateCommon* card3 = new CardTemplateCommon(c3, {700 + 150, 700}, {200, 300}, 30);
    CardTemplateCommon* card4 = new CardTemplateCommon(c4, {700 + 300, 700}, {200, 300}, 40);


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