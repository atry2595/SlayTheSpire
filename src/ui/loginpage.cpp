#include "loginpage.h"
#include "ui_loginpage.h"
#include <QMessageBox>

LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    connect(ui->usernameLineEdit,
            &QLineEdit::returnPressed,
            ui->loginButton,
            &QPushButton::click);

    connect(ui->passwordLineEdit,
            &QLineEdit::returnPressed,
            ui->loginButton,
            &QPushButton::click);
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_signUpButton_clicked()
{
    emit openRegisterPage();

}


void LoginPage::on_forgotPasswordButton_clicked()
{
    emit openForgotPasswordPage();
}

void LoginPage::setFileManager(FileManager *manager)
{
    fileManager = manager;
}

void LoginPage::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();

    Player *player = fileManager->login(username, password);

    if(player)
    {
        QMessageBox::information(this,
                                 "Login",
                                 "Login successful!");

        ui->usernameLineEdit->clear();
        ui->passwordLineEdit->clear();
        emit loginSuccessful();
    }
    else
    {
        QMessageBox::warning(this,
                             "Login",
                             "Invalid username or password.");
    }
}

