#include "playmenu.h"
#include "ui_playmenu.h"

PlayMenu::PlayMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlayMenu)
{
    ui->setupUi(this);
}

PlayMenu::~PlayMenu()
{
    delete ui;
}

void PlayMenu::on_backButton_clicked()
{
    emit backToMenu();
}