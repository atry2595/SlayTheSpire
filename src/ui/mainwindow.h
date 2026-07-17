#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStackedWidget>
#include "LoginPage.h"
#include <QMainWindow>
#include <QStackedWidget>

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
    QStackedWidget* stack;
    Ui::MainWindow *ui;
    QStackedWidget *stack;
    LoginPage *loginPage;
};
#endif // MAINWINDOW_H
