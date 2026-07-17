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
    ui->setupUi(this);

    stack = new QStackedWidget(this);

    loginPage = new LoginPage();

    stack->addWidget(loginPage);

    setCentralWidget(stack);

    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

