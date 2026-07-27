#ifndef FORGOTPASSWORDPAGE_H
#define FORGOTPASSWORDPAGE_H
#include "core/login/filemanager.h"

#include <QMainWindow>

namespace Ui {
class ForgotPasswordPage;
}

class ForgotPasswordPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit ForgotPasswordPage(QWidget *parent = nullptr);
    ~ForgotPasswordPage();
    void setFileManager(FileManager *manager);
    void clearFields();

private:
    Ui::ForgotPasswordPage *ui;
    FileManager *fileManager = nullptr;

    void showEmailError(const QString &message);
    void showPasswordError(const QString &message);
    void showConfirmPasswordError(const QString &message);
    void showSuccess(const QString &message);

    void clearErrors();

    void setEmailNormalStyle();
    void setEmailErrorStyle();

    void setPasswordNormalStyle();
    void setPasswordErrorStyle();

    void setConfirmPasswordNormalStyle();
    void setConfirmPasswordErrorStyle();

    QAction *passwordEyeAction;
    QAction *confirmEyeAction;

signals:
    void openLoginPage();
private slots:
    void on_loginButton_clicked();
    void on_changePasswordButton_clicked();
};

#endif // FORGOTPASSWORDPAGE_H
