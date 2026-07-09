#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "combatpage.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    stack = new QStackedWidget(this);
    stack->addWidget(new CombatPage());
    setCentralWidget(stack);
    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

