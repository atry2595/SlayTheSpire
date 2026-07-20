#include "registerpage.h"
#include "ui_registerpage.h"
#include <QMessageBox>
#include <QAction>
#include <QIcon>
#include <QLineEdit>
#include <QTimer>

RegisterPage::RegisterPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterPage)
{
    ui->setupUi(this);
    ui->usernameSuggestionLabel->hide();
    ui->usernameSuggestionLabel->setTextFormat(Qt::RichText);
    ui->usernameSuggestionLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);
    ui->usernameSuggestionLabel->setOpenExternalLinks(false);

    ui->usernameErrorLabel->hide();
    ui->emailErrorLabel->hide();
    ui->passwordErrorLabel->hide();
    ui->confirmPasswordErrorLabel->hide();
    ui->successLabel->hide();

    passwordEyeAction = ui->passwordLineEdit->addAction(
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

    connect(ui->usernameLineEdit,
            &QLineEdit::textChanged,
            this,
            [this]()
            {
                if(ui->usernameSuggestionLabel->isVisible())
                {
                    ui->usernameSuggestionLabel->hide();
                    setUsernameNormalStyle();
                }
            });

    connect(ui->usernameSuggestionLabel,
            &QLabel::linkActivated,
            this,
            [this](const QString &link)
            {
                ui->usernameLineEdit->setText(link);

                ui->usernameSuggestionLabel->hide();

                setUsernameNormalStyle();
            });



    confirmEyeAction = ui->confirmPasswordLineEdit->addAction(
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
    clearErrors();

    ui->usernameSuggestionLabel->hide();
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    passwordEyeAction->setIcon(QIcon(":/icon/login/eye_off.svg"));
    confirmEyeAction->setIcon(QIcon(":/icon/login/eye_off.svg"));
    setUsernameNormalStyle();
}

void RegisterPage::setUsernameNormalStyle()
{
    ui->usernameLineEdit->setStyleSheet(
        "QLineEdit {"
        "background-color: #404040;"
        "border: 1px solid #666666;"
        "border-radius: 10px;"
        "padding: 13px;"
        "color: white;"
        "min-height: 28px;"
        "}"
        "QLineEdit:focus {"
        "border: 2px solid #8c8c8c;"
        "}"
        );

    ui->usernameLabel->setStyleSheet(
        "color:white;"
        "font-size:16px;"
        "font-weight:600;");
}

void RegisterPage::setUsernameErrorStyle()
{
    ui->usernameLineEdit->setStyleSheet(
        "QLineEdit {"
        "background-color: #404040;"
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

    ui->usernameLabel->setStyleSheet(
        "color:red;"
        "font-size:16px;"
        "font-weight:600;");
}

void RegisterPage::showUsernameError(const QString &message)
{
    ui->usernameErrorLabel->setText(message);
    ui->usernameErrorLabel->show();

    setUsernameErrorStyle();
}

void RegisterPage::showEmailError(const QString &message)
{
    ui->emailErrorLabel->setText(message);
    ui->emailErrorLabel->show();
}

void RegisterPage::showPasswordError(const QString &message)
{
    ui->passwordErrorLabel->setText(message);
    ui->passwordErrorLabel->show();
}

void RegisterPage::showConfirmPasswordError(const QString &message)
{
    ui->confirmPasswordErrorLabel->setText(message);
    ui->confirmPasswordErrorLabel->show();
}

void RegisterPage::clearErrors()
{
    ui->usernameErrorLabel->hide();
    ui->emailErrorLabel->hide();
    ui->passwordErrorLabel->hide();
    ui->confirmPasswordErrorLabel->hide();
    ui->successLabel->hide();

    setUsernameNormalStyle();
}

void RegisterPage::showSuccess(const QString &message)
{
    ui->successLabel->setText(message);
    ui->successLabel->show();
}

void RegisterPage::on_signUpButton_clicked()
{
    QString username = ui->usernameLineEdit->text().trimmed();
    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    QString errorMessage;

    clearErrors();

    ui->usernameSuggestionLabel->hide();

    bool success = fileManager->registerPlayer(
        username,
        email,
        password,
        confirmPassword,
        errorMessage);

    if(success)
    {
        showSuccess("Registration completed successfully.");

        QTimer::singleShot(1000, this,
                           [this]()
                           {
                               clearFields();

                               emit openLoginPage();
                           });
    }
    else
    {
        if(errorMessage == "Username already exists.")
        {
            QStringList suggestions =
                fileManager->getUsernameSuggestions(username);

            QString message;

            message += "You can use:<br>";

            for(const QString &name : suggestions)
            {
                message += "<a href=\"" + name + "\">" + name + "</a><br>";
            }

            showUsernameError("Username already exists.");

            ui->usernameSuggestionLabel->setText(message);

            ui->usernameSuggestionLabel->show();

            return;
        }

        if(errorMessage == "Email already exists."
            || errorMessage == "Invalid email.")
        {
            showEmailError(errorMessage);
            return;
        }

        if(errorMessage == "Passwords do not match.")
        {
            showConfirmPasswordError(errorMessage);
            return;
        }

        if(errorMessage.contains("Password"))
        {
            showPasswordError(errorMessage);
            return;
        }
    }
}
