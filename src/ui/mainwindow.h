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
};

#endif // MAINWINDOW_H