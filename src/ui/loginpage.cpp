#include "loginpage.h"
#include "ui_loginpage.h"
#include <QAction>
#include <QIcon>
#include <QLineEdit>
#include <QTimer>

LoginPage::LoginPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
    ui->usernameErrorLabel->hide();
    ui->passwordErrorLabel->hide();
    ui->successLabel->hide();

    passwordEyeAction = ui->passwordLineEdit->addAction(
        QIcon(":/icon/login/eye_off.svg"),
        QLineEdit::TrailingPosition);

    connect(passwordEyeAction,
            &QAction::triggered,
            this,
            [this]()
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

    connect(ui->usernameLineEdit,
            &QLineEdit::returnPressed,
            ui->loginButton,
            &QPushButton::click);

    connect(ui->passwordLineEdit,
            &QLineEdit::returnPressed,
            ui->loginButton,
            &QPushButton::click);

    connect(ui->usernameLineEdit,
            &QLineEdit::textChanged,
            this,
            [this]()
            {
                clearErrors();
            });

    connect(ui->passwordLineEdit,
            &QLineEdit::textChanged,
            this,
            [this]()
            {
                clearErrors();
            });

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

void LoginPage::clearFields()
{
    ui->usernameLineEdit->clear();
    ui->passwordLineEdit->clear();

    clearErrors();

    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);

    passwordEyeAction->setIcon(
        QIcon(":/icon/login/eye_off.svg"));
}

void LoginPage::setUsernameNormalStyle()
{
    ui->usernameLineEdit->setStyleSheet(
        "QLineEdit {"
        "background-color:#404040;"
        "border:1px solid #666666;"
        "border-radius:10px;"
        "padding:13px;"
        "color:white;"
        "min-height:28px;"
        "}"
        "QLineEdit:focus {"
        "border:2px solid #8c8c8c;"
        "}"
        );
    ui->username->setStyleSheet(
        "color:white;"
        "font-size:16px;"
        "font-weight:600;");
}

void LoginPage::setUsernameErrorStyle()
{
    ui->usernameLineEdit->setStyleSheet(
        "QLineEdit {"
        "background-color:#404040;"
        "border:2px solid red;"
        "border-radius:10px;"
        "padding:13px;"
        "color:white;"
        "min-height:28px;"
        "}"
        "QLineEdit:focus {"
        "border:2px solid red;"
        "}"
        );
    ui->username->setStyleSheet(
        "color:red;"
        "font-size:16px;"
        "font-weight:600;");
}

void LoginPage::setPasswordNormalStyle()
{
    ui->passwordLineEdit->setStyleSheet(
        "QLineEdit {"
        "background-color:#404040;"
        "border:1px solid #666666;"
        "border-radius:10px;"
        "padding:13px;"
        "color:white;"
        "min-height:28px;"
        "}"
        "QLineEdit:focus {"
        "border:2px solid #8c8c8c;"
        "}"
        );
    ui->Password->setStyleSheet(
        "color:white;"
        "font-size:16px;"
        "font-weight:600;");
}

void LoginPage::setPasswordErrorStyle()
{
    ui->passwordLineEdit->setStyleSheet(
        "QLineEdit {"
        "background-color:#404040;"
        "border:2px solid red;"
        "border-radius:10px;"
        "padding:13px;"
        "color:white;"
        "min-height:28px;"
        "}"
        "QLineEdit:focus {"
        "border:2px solid red;"
        "}"
        );
    ui->Password->setStyleSheet(
        "color:red;"
        "font-size:16px;"
        "font-weight:600;");
}

void LoginPage::showUsernameError(const QString &message)
{
    ui->usernameErrorLabel->setText(message);
    ui->usernameErrorLabel->show();
    setUsernameErrorStyle();

}

void LoginPage::showPasswordError(const QString &message)
{
    ui->passwordErrorLabel->setText(message);
    ui->passwordErrorLabel->show();
    setPasswordErrorStyle();

}

void LoginPage::showSuccess(const QString &message)
{
    ui->successLabel->setText(message);
    ui->successLabel->show();
}

void LoginPage::clearErrors()
{
    ui->usernameErrorLabel->hide();
    ui->passwordErrorLabel->hide();
    ui->successLabel->hide();

    setUsernameNormalStyle();
    setPasswordNormalStyle();
}

void LoginPage::on_loginButton_clicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    clearErrors();

    bool hasError = false;

    if(username.isEmpty())
    {
        showUsernameError("Please enter your username.");
        hasError = true;
    }

    if(password.isEmpty())
    {
        showPasswordError("Please enter your password.");
        hasError = true;
    }

    if(hasError)
    {
        return;
    }

    Player *player = fileManager->login(username, password);

    if(player)
    {
        showSuccess("Login successful!");

        QTimer::singleShot(2000,
                           this,
                           [this]()
                           {
                               clearFields();

                               emit loginSuccessful();
                           });

        return;
    }

    ui->passwordErrorLabel->setText("Invalid username or password.");
    ui->passwordErrorLabel->show();
}

