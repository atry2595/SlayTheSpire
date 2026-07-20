#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include "core/login/filemanager.h"
#include <QMainWindow>

namespace Ui {
class RegisterPage;
}

class RegisterPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterPage(QWidget *parent = nullptr);
    ~RegisterPage();
    void setFileManager(FileManager *manager);
    void clearFields();

private slots:
    void on_loginButton_clicked();

    void on_signUpButton_clicked();

private:
    Ui::RegisterPage *ui;
    FileManager *fileManager = nullptr;

    void setUsernameNormalStyle();
    void setUsernameErrorStyle();

    void showUsernameError(const QString &message);
    void showEmailError(const QString &message);
    void showPasswordError(const QString &message);
    void showConfirmPasswordError(const QString &message);

    void showSuccess(const QString &message);

    QAction *passwordEyeAction;
    QAction *confirmEyeAction;

    void clearUsernameError();
    void clearEmailError();
    void clearPasswordError();
    void clearConfirmPasswordError();

    void clearErrors();


signals:
    void openLoginPage();
};

#endif // REGISTERPAGE_H
