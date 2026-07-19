#include "forgotpasswordpage.h"
#include "ui_forgotpasswordpage.h"
#include <QMessageBox>
#include <QAction>
#include <QIcon>
#include <QLineEdit>

ForgotPasswordPage::ForgotPasswordPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ForgotPasswordPage)
{
    ui->setupUi(this);

    QAction *passwordEyeAction = ui->newPasswordLineEdit->addAction(
        QIcon(":/icon/login/eye_off.svg"),
        QLineEdit::TrailingPosition);

    connect(passwordEyeAction, &QAction::triggered, this,
            [this, passwordEyeAction]()
            {
                if(ui->newPasswordLineEdit->echoMode() == QLineEdit::Password)
                {
                    ui->newPasswordLineEdit->setEchoMode(QLineEdit::Normal);
                    passwordEyeAction->setIcon(QIcon(":/icon/login/eye.svg"));
                }
                else
                {
                    ui->newPasswordLineEdit->setEchoMode(QLineEdit::Password);
                    passwordEyeAction->setIcon(QIcon(":/icon/login/eye_off.svg"));
                }
            });



    QAction *confirmEyeAction = ui->confirmPasswordLineEdit->addAction(
        QIcon(":/icon/login/eye_off.svg"),
        QLineEdit::TrailingPosition);

    connect(confirmEyeAction, &QAction::triggered, this,
            [this, confirmEyeAction]()
            {
                if(ui->confirmPasswordLineEdit->echoMode() == QLineEdit::Password)
                {
                    ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Normal);
                    confirmEyeAction->setIcon(QIcon(":/icon/login/eye.svg"));
                }
                else
                {
                    ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
                    confirmEyeAction->setIcon(QIcon(":/icon/login/eye_off.svg"));
                }
            });

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

