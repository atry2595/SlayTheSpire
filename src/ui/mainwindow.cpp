#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "combatpage.h"
#include "entity/ironclad.h"
#include "entity/taskmaster.h"
#include "entity/gremlin_nob.h"
#include "entity/spheric_guardian.h"
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
    auto pll = new ironclad(eve);
    auto en1 = spheric_guardian::create(acts);
    auto en2 = spheric_guardian::create(acts);
    combat_manager* com = new combat_manager({pl, pll}, {en1, en2}, entityType::monster, eve);
    auto cp = new CombatPage(nullptr, com);

    stack = new QStackedWidget(this);
    stack->addWidget(cp);
    setCentralWidget(stack);
    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

