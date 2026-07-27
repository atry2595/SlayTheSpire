#include "forgotpasswordpage.h"
#include "ui_forgotpasswordpage.h"
#include <QAction>
#include <QIcon>
#include <QLineEdit>
#include <QTimer>

ForgotPasswordPage::ForgotPasswordPage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ForgotPasswordPage)
{
    ui->setupUi(this);

    ui->emailErrorLabel->hide();
    ui->newPasswordErrorLabel->hide();
    ui->confirmPasswordErrorLabel->hide();
    ui->successLabel->hide();

    passwordEyeAction = ui->newPasswordLineEdit->addAction(
        QIcon(":/icon/login/eye_off.svg"),
        QLineEdit::TrailingPosition);

    connect(passwordEyeAction, &QAction::triggered, this,
            [this]()
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



    confirmEyeAction = ui->confirmPasswordLineEdit->addAction(
        QIcon(":/icon/login/eye_off.svg"),
        QLineEdit::TrailingPosition);

    connect(confirmEyeAction, &QAction::triggered, this,
            [this]()
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

    connect(ui->emailLineEdit,
            &QLineEdit::textChanged,
            this,
            [this]()
            {
                ui->emailErrorLabel->hide();
                setEmailNormalStyle();
            });

    connect(ui->newPasswordLineEdit,
            &QLineEdit::textChanged,
            this,
            [this]()
            {
                ui->newPasswordErrorLabel->hide();
                setPasswordNormalStyle();
            });

    connect(ui->confirmPasswordLineEdit,
            &QLineEdit::textChanged,
            this,
            [this]()
            {
                ui->confirmPasswordErrorLabel->hide();
                setConfirmPasswordNormalStyle();
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

void ForgotPasswordPage::clearFields()
{
    ui->emailLineEdit->clear();
    ui->newPasswordLineEdit->clear();
    ui->confirmPasswordLineEdit->clear();

    clearErrors();

    ui->newPasswordLineEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

    passwordEyeAction->setIcon(
        QIcon(":/icon/login/eye_off.svg"));

    confirmEyeAction->setIcon(
        QIcon(":/icon/login/eye_off.svg"));
}

void ForgotPasswordPage::showEmailError(const QString &message)
{
    ui->emailErrorLabel->setText(message);
    ui->emailErrorLabel->show();

    setEmailErrorStyle();
}

void ForgotPasswordPage::showPasswordError(const QString &message)
{
    ui->newPasswordErrorLabel->setText(message);
    ui->newPasswordErrorLabel->show();

    setPasswordErrorStyle();
}

void ForgotPasswordPage::showConfirmPasswordError(const QString &message)
{
    ui->confirmPasswordErrorLabel->setText(message);
    ui->confirmPasswordErrorLabel->show();

    setConfirmPasswordErrorStyle();
}

void ForgotPasswordPage::showSuccess(const QString &message)
{
    ui->successLabel->setText(message);
    ui->successLabel->show();
}

void ForgotPasswordPage::clearErrors()
{
    ui->emailErrorLabel->hide();
    ui->newPasswordErrorLabel->hide();
    ui->confirmPasswordErrorLabel->hide();
    ui->successLabel->hide();

    setEmailNormalStyle();
    setPasswordNormalStyle();
    setConfirmPasswordNormalStyle();
}

void ForgotPasswordPage::setEmailNormalStyle()
{
    ui->emailLineEdit->setStyleSheet(
        "QLineEdit{"
        "background:#404040;"
        "border:1px solid #666666;"
        "border-radius:10px;"
        "padding:13px;"
        "color:white;"
        "}"
        "QLineEdit:focus{"
        "border:2px solid #8c8c8c;"
        "}");

    ui->emailLabel->setStyleSheet(
        "color:white;"
        "font-size:16px;"
        "font-weight:600;");
}

void ForgotPasswordPage::setEmailErrorStyle()
{
    ui->emailLineEdit->setStyleSheet(
        "QLineEdit{"
        "background:#404040;"
        "border:2px solid red;"
        "border-radius:10px;"
        "padding:13px;"
        "color:white;"
        "}"
        "QLineEdit:focus{"
        "border:2px solid red;"
        "}");

    ui->emailLabel->setStyleSheet(
        "color:red;"
        "font-size:16px;"
        "font-weight:600;");
}

void ForgotPasswordPage::setPasswordNormalStyle()
{
    ui->newPasswordLineEdit->setStyleSheet(
        "QLineEdit{"
        "background:#404040;"
        "border:1px solid #666666;"
        "border-radius:10px;"
        "padding:13px;"
        "color:white;"
        "}"
        "QLineEdit:focus{"
        "border:2px solid #8c8c8c;"
        "}");

    ui->newPasswordLabel->setStyleSheet(
        "color:white;"
        "font-size:16px;"
        "font-weight:600;");
}

void ForgotPasswordPage::setPasswordErrorStyle()
{
    ui->newPasswordLineEdit->setStyleSheet(
        "QLineEdit{"
        "background:#404040;"
        "border:2px solid red;"
        "border-radius:10px;"
        "padding:13px;"
        "color:white;"
        "}"
        "QLineEdit:focus{"
        "border:2px solid red;"
        "}");

    ui->newPasswordLabel->setStyleSheet(
        "color:red;"
        "font-size:16px;"
        "font-weight:600;");
}

void ForgotPasswordPage::setConfirmPasswordNormalStyle()
{
    ui->confirmPasswordLineEdit->setStyleSheet(
        "QLineEdit{"
        "background:#404040;"
        "border:1px solid #666666;"
        "border-radius:10px;"
        "padding:13px;"
        "color:white;"
        "}"
        "QLineEdit:focus{"
        "border:2px solid #8c8c8c;"
        "}");

    ui->confirmPasswordLabel->setStyleSheet(
        "color:white;"
        "font-size:16px;"
        "font-weight:600;");
}

void ForgotPasswordPage::setConfirmPasswordErrorStyle()
{
    ui->confirmPasswordLineEdit->setStyleSheet(
        "QLineEdit{"
        "background:#404040;"
        "border:2px solid red;"
        "border-radius:10px;"
        "padding:13px;"
        "color:white;"
        "}"
        "QLineEdit:focus{"
        "border:2px solid red;"
        "}");

    ui->confirmPasswordLabel->setStyleSheet(
        "color:red;"
        "font-size:16px;"
        "font-weight:600;");
}

void ForgotPasswordPage::on_changePasswordButton_clicked()
{
    QString email = ui->emailLineEdit->text().trimmed();
    QString newPassword = ui->newPasswordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();

    clearErrors();

    bool hasError = false;

    if(email.isEmpty())
    {
        showEmailError("Please enter your email.");
        hasError = true;
    }

    if(newPassword.isEmpty())
    {
        showPasswordError("Please enter your password.");
        hasError = true;
    }

    if(confirmPassword.isEmpty())
    {
        showConfirmPasswordError("Please confirm your password.");
        hasError = true;
    }

    if(hasError)
    {
        return;
    }

    QString errorMessage;

    bool success = fileManager->resetPassword(
        email,
        newPassword,
        confirmPassword,
        errorMessage);

    if(success)
    {
        clearErrors();

        showSuccess("Password changed successfully.");

        QTimer::singleShot(
            2000,
            this,
            [this]()
            {
                clearFields();

                emit openLoginPage();
            });

        return;
    }

    if(errorMessage == "Email not found.")
    {
        showEmailError(errorMessage);
        return;
    }

    if(errorMessage == "Passwords do not match.")
    {
        showConfirmPasswordError(errorMessage);
        return;
    }

    showPasswordError(errorMessage);
}

