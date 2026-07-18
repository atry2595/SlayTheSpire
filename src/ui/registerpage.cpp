#include "registerpage.h"
#include "ui_registerpage.h"
#include <QMessageBox>

RegisterPage::RegisterPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterPage)
{
    ui->setupUi(this);
    connect(ui->usernameLineEdit,
            &QLineEdit::returnPressed,
            ui->signUpButton,
            &QPushButton::click);

    connect(ui->emailLineEdit,
            &QLineEdit::returnPressed,
            ui->signUpButton,
            &QPushButton::click);

    connect(ui->passwordLineEdit,
            &QLineEdit::returnPressed,
            ui->signUpButton,
            &QPushButton::click);

    connect(ui->confirmPasswordLineEdit,
            &QLineEdit::returnPressed,
            ui->signUpButton,
            &QPushButton::click);
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
        QMessageBox::warning(
            this,
            "Register",
            errorMessage
            );
    }
}
