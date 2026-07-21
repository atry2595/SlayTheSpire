#include "playmenu.h"
#include "ui_playmenu.h"

playmenu::playmenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::playmenu)
{
    ui->setupUi(this);
}

playmenu::~playmenu()
{
    delete ui;
}
