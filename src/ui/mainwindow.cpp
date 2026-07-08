#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "combatpage.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    showFullScreen();
    stack = new QStackedWidget(this);
    stack->addWidget(new CombatPage());
    setCentralWidget(stack);
}

MainWindow::~MainWindow()
{
    delete ui;
}

