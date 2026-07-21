#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_playButton_clicked()
{
    emit openPlayPage();
}

void Menu::on_statisticsButton_clicked()
{
    emit openStatisticsPage();
}

void Menu::on_settingsButton_clicked()
{
    emit openSettingsPage();
}

void Menu::on_exitButton_clicked()
{
    emit exitGame();
}