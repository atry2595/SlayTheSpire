#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include "core/login/filemanager.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();
    void setFileManager(FileManager *manager);

private slots:
    void on_signUpButton_clicked();

    void on_forgotPasswordButton_clicked();

    void on_loginButton_clicked();

private:
    Ui::LoginPage *ui;
    FileManager *fileManager = nullptr;

signals:
    void openRegisterPage();
    void openForgotPasswordPage();
    void loginSuccessful();

};

#endif // LOGINPAGE_H
