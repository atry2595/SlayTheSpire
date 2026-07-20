#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStackedWidget>
#include "loginpage.h"
#include "core/menu/menu.h"
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
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    FileManager *fileManager;
    Ui::MainWindow *ui;
    QStackedWidget *stack;
    LoginPage *loginPage;
    RegisterPage *registerPage;
    ForgotPasswordPage *forgotPasswordPage;

};
#endif // MAINWINDOW_H
