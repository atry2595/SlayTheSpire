#include "registerpage.h"
#include "ui_registerpage.h"
#include <QMessageBox>
#include <QAction>
#include <QIcon>
#include <QLineEdit>

RegisterPage::RegisterPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterPage)
{
    ui->setupUi(this);
    ui->usernameSuggestionLabel->hide();

    QAction *passwordEyeAction = ui->passwordLineEdit->addAction(
        QIcon(":/icon/login/eye_off.svg"),
        QLineEdit::TrailingPosition);

    connect(passwordEyeAction, &QAction::triggered, this,
            [this, passwordEyeAction]()
            {
                if(ui->passwordLineEdit->echoMode() == QLineEdit::Password)
                {
                    ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
                    passwordEyeAction->setIcon(QIcon(":/icon/login/eye.svg"));
                }
                else
                {
                    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
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

RegisterPage::~RegisterPage()
{
    delete ui;
}
void RegisterPage::on_loginButton_clicked()
{
    emit openLoginPage();
}

void RegisterPage::setFileManager(FileManager *manager)
{
    fileManager = manager;
}

void RegisterPage::clearFields()
{
    ui->usernameLineEdit->clear();
    ui->emailLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->confirmPasswordLineEdit->clear();
}

void RegisterPage::on_signUpButton_clicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    QString errorMessage;

    bool success = fileManager->registerPlayer(
        username,
        email,
        password,
        confirmPassword,
        errorMessage);

    if(success)
    {
        QMessageBox::information(
            this,
            "Register",
            "Registration successful!"
            );
        ui->usernameLineEdit->clear();
        ui->emailLineEdit->clear();
        ui->passwordLineEdit->clear();
        ui->confirmPasswordLineEdit->clear();

        emit openLoginPage();
    }
    else
    {
        if(errorMessage == "Username already exists.")
        {
            QStringList suggestions =
                fileManager->getUsernameSuggestions(username);

            QString message = errorMessage;
            message += "\n\nSuggested usernames:\n";

            for(const QString &name : suggestions)
            {
                message += "• " + name + "\n";
            }

            QMessageBox::warning(
                this,
                "Register",
                message
                );
        }
        else
        {
            QMessageBox::warning(
                this,
                "Register",
                errorMessage
                );
        }
    }

}
