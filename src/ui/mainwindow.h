#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStackedWidget>
#include "loginpage.h"
#include <QMainWindow>
#include "registerpage.h"
#include "forgotpasswordpage.h"

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

private:
    Ui::MainWindow *ui;

    FileManager *fileManager;

    QStackedWidget *authStack;

    QStackedWidget *mainStack;

    LoginPage *loginPage;
    RegisterPage *registerPage;
    ForgotPasswordPage *forgotPasswordPage;

    void showMainMenu();
};


#endif // MAINWINDOW_H
