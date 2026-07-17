#include "registerpage.h"
#include "ui_registerpage.h"
#include <QMessageBox>

RegisterPage::RegisterPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterPage)
{
    ui->setupUi(this);
}

RegisterPage::~RegisterPage()
{
    delete ui;
}

void RegisterPage::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    QString errorMessage;

    bool success = fileManager->registerPlayer(username,email,password,confirmPassword,errorMessage);

    if(success)
    {
        QMessageBox::information(this,"Register","Registration successful!");

        emit openLoginPage();
    }
    else
    {
        QMessageBox::warning(this,"Register",errorMessage);
    }
}

void RegisterPage::setFileManager(FileManager *manager)
{
    fileManager = manager;
}
