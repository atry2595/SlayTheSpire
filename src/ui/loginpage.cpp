#include "loginpage.h"
#include "ui_loginpage.h"
#include <QMessageBox>
#include <QAction>
#include <QIcon>
#include <QLineEdit>

LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    QAction *eyeAction = ui->passwordLineEdit->addAction(
        QIcon(":/icon/login/eye_off.svg"),
        QLineEdit::TrailingPosition);

    connect(eyeAction, &QAction::triggered, this,
            [this, eyeAction]()
            {
                if (ui->passwordLineEdit->echoMode() == QLineEdit::Password)
                {
                    ui->passwordLineEdit->setEchoMode(QLineEdit::Normal);
                    eyeAction->setIcon(QIcon(":/icon/login/eye.svg"));
                }
                else
                {
                    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
                    eyeAction->setIcon(QIcon(":/icon/login/eye_off.svg"));
                }
            });

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

