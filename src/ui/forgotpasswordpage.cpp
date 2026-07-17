#include "forgotpasswordpage.h"
#include "ui_forgotpasswordpage.h"

ForgotPasswordPage::ForgotPasswordPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ForgotPasswordPage)
{
    ui->setupUi(this);
}

ForgotPasswordPage::~ForgotPasswordPage()
{
    delete ui;
}
void ForgotPasswordPage::on_loginButton_clicked()
{
    emit openLoginPage();

}

