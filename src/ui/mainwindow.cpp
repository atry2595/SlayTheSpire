#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "combatpage.h"
#include "entity/ironclad.h"
#include "entity/book_of_stabbing.h"
#include "combat/combat_event.h"
#include "combat/game_action.h"
#include "items/potions/potionfactory.h"
#include "items/relics/relicfactory.h"
#include "combat/manageCombat/combat_manager.h"
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    combatEvent* eve = new combatEvent();
    game_action acts(eve);

    auto pl = new ironclad(eve);
    pl->potion_list_add(PotionFactory::createPotion(potionID::block_potion, pl));
    pl->potion_list_add(PotionFactory::createPotion(potionID::fear_potion, pl));
    pl->potion_list_add(PotionFactory::createPotion(potionID::fairy_in_a_bottle, pl));
    pl->add_relic(acts, RelicFactory::createRelic(relicID::blood_vial, pl));
    pl->add_relic(acts, RelicFactory::createRelic(relicID::shuriken, pl));
    pl->add_relic(acts, RelicFactory::createRelic(relicID::horn_cleat, pl));
    auto en2 = book_of_stabbing::create(acts);
    combat_manager* com = new combat_manager({pl}, {en2}, CombatType::elite, eve);
    auto cp = new CombatPage(nullptr, com, pl);


    stack = new QStackedWidget(this);
    stack->addWidget(cp);
    setCentralWidget(stack);
    showFullScreen();

    QTimer* t = new QTimer();
    t->start(1000);
    connect(t, &QTimer::timeout, this, [=](){
        t->stop();
        com->combat_start();
    });
    connect(eve, &combatEvent::nextAction, this, [=](){ cp->Delete(); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

