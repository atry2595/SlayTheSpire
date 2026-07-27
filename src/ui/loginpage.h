#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include "core/login/filemanager.h"

namespace Ui {
class LoginPage;
}

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

    void setFileManager(FileManager *manager);
    void clearFields();

private slots:
    void on_signUpButton_clicked();
    void on_forgotPasswordButton_clicked();
    void on_loginButton_clicked();

private:
    Ui::LoginPage *ui;
    FileManager *fileManager = nullptr;
    QAction *passwordEyeAction;

    void showUsernameError(const QString &message);
    void showPasswordError(const QString &message);
    void setUsernameNormalStyle();
    void setUsernameErrorStyle();
    void setPasswordNormalStyle();
    void setPasswordErrorStyle();
    void showSuccess(const QString &message);
    void clearErrors();

signals:
    void openRegisterPage();
    void openForgotPasswordPage();
    void loginSuccessful();
};

#endif // LOGINPAGE_H
