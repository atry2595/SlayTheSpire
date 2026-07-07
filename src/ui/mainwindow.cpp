#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "combatpage.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    stack = new QStackedWidget(this);
    setCentralWidget(stack);
    stack->addWidget(new CombatPage());
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

