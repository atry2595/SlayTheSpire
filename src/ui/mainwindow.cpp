#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map/map.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Map map;

    map.generate();

    qDebug() << map.toDebugString();
}

MainWindow::~MainWindow()
{
    delete ui;
}

