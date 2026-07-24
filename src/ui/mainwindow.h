#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QTableWidget>
#include <QHeaderView>
#include "loginpage.h"
#include "registerpage.h"
#include "forgotpasswordpage.h"
#include "core/login/leaderboard.h"
#include "core/login/filemanager.h"
#include "core/login/stats.h"
#include <QEvent>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void on_playButton_clicked();
    void on_statisticsButton_clicked();
    void on_settingsButton_clicked();
    void on_exitButton_clicked();

    void on_backButton_clicked();
    void on_backButton_2_clicked();
    void on_leaderBoardButton_clicked();
    void on_backButton_3_clicked();

    void updateLeaderboardUI();

    void on_personalStatisticsButton_clicked();
    void on_backFromStatsButton_clicked();

    void onButtonHovered();

private:
    Ui::MainWindow *ui;

    FileManager *fileManager;
    Leaderboard *leaderboard;

    QStackedWidget *authStack;
    QStackedWidget *mainStack;

    LoginPage *loginPage;
    RegisterPage *registerPage;
    ForgotPasswordPage *forgotPasswordPage;

    void showMainMenu();
    void setupLeaderboardTable();

    void updatePersonalStatsUI();

    void setupButtonHoverEffects();
};

#endif // MAINWINDOW_H