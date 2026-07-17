#ifndef FORGOTPASSWORDPAGE_H
#define FORGOTPASSWORDPAGE_H

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

private:
    Ui::ForgotPasswordPage *ui;

signals:
    void openLoginPage();
private slots:
    void on_loginButton_clicked();
};

#endif // FORGOTPASSWORDPAGE_H
