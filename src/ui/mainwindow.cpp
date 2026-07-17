#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "combatpage.h"
#include "entity/ironclad.h"
#include "entity/spheric_guardian.h"
#include "entity/small_slime.h"
#include "entity/green_louse.h"
#include "combat/combat_event.h"
#include "combat/game_action.h"
#include "combat/manageCombat/combat_manager.h"
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    combatEvent* eve = new combatEvent();
    game_action acts(eve);

    auto pl = new ironclad(eve);
    auto en1 = small_slime::create(acts);
    auto en2 = small_slime::create(acts);
    auto en3 = small_slime::create(acts);
    auto en4 = small_slime::create(acts);
    auto en5 = small_slime::create(acts);
    auto en6 = small_slime::create(acts);
    auto en7 = small_slime::create(acts);
    auto en8 = small_slime::create(acts);
    auto en9 = small_slime::create(acts);
    auto en0 = small_slime::create(acts);
    combat_manager* com = new combat_manager({pl}, {en1, en2, en3, en4, en5 , en6, en7, en8, en9, en0}, entityType::monster, eve);
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

