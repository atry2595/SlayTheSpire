#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map/map.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Map map;

    map.generate();

    std::cout << map.debugMap().toStdString() << std::endl;

    qDebug().noquote() << map.debugMap();
}

MainWindow::~MainWindow()
{
    delete ui;
}

