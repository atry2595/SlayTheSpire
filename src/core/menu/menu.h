#ifndef MENU_H
#define MENU_H

#include <QObject>
#include <QMainWindow>
#include "playmenu.h"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

private:
    Ui::Menu *ui;

signals:
    void openPlayPage();
    void openStatisticsPage();
    void openSettingsPage();
    void exitGame();

private slots:
    void on_playButton_clicked();
    void on_statisticsButton_clicked();
    void on_settingsButton_clicked();
    void on_exitButton_clicked();
    نف

};

#endif // MENU_H
