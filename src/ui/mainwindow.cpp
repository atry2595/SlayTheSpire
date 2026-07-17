#include "mainwindow.h"
#include "ui_mainwindow.h"

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
