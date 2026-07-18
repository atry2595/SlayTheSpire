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

private:
    Ui::ForgotPasswordPage *ui;
    FileManager *fileManager = nullptr;

signals:
    void openLoginPage();
private slots:
    void on_loginButton_clicked();
    void on_changePasswordButton_clicked();
};

#endif // FORGOTPASSWORDPAGE_H
