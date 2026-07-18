#include "forgotpasswordpage.h"
#include "ui_forgotpasswordpage.h"
#include <QMessageBox>

ForgotPasswordPage::ForgotPasswordPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ForgotPasswordPage)
{
    ui->setupUi(this);
    connect(ui->emailLineEdit,
            &QLineEdit::returnPressed,
            ui->changePasswordButton,
            &QPushButton::click);

    connect(ui->newPasswordLineEdit,
            &QLineEdit::returnPressed,
            ui->changePasswordButton,
            &QPushButton::click);

    connect(ui->confirmPasswordLineEdit,
            &QLineEdit::returnPressed,
            ui->changePasswordButton,
            &QPushButton::click);
}

ForgotPasswordPage::~ForgotPasswordPage()
{
    delete ui;
}
void ForgotPasswordPage::on_loginButton_clicked()
{
    emit openLoginPage();

}

void ForgotPasswordPage::setFileManager(FileManager *manager)
{
    fileManager = manager;
}

void ForgotPasswordPage::on_changePasswordButton_clicked()
{
    QString email = ui->emailLineEdit->text().trimmed();
    QString newPassword = ui->newPasswordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    QString errorMessage;

    bool success = fileManager->resetPassword(
        email,
        newPassword,
        confirmPassword,
        errorMessage);

    if(success)
    {
        QMessageBox::information(
            this,
            "Success",
            "Password changed successfully.");

        ui->emailLineEdit->clear();
        ui->newPasswordLineEdit->clear();
        ui->confirmPasswordLineEdit->clear();

        emit openLoginPage();
    }
    else
    {
        QMessageBox::warning(
            this,
            "Error",
            errorMessage);
    }
}

