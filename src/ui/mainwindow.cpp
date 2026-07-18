#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fileManager = new FileManager();

    loginPage = new LoginPage();
    registerPage = new RegisterPage();
    forgotPasswordPage = new ForgotPasswordPage();

    loginPage->setFileManager(fileManager);
    registerPage->setFileManager(fileManager);
    forgotPasswordPage->setFileManager(fileManager);

    stack = new QStackedWidget(this);

    stack->addWidget(loginPage);
    stack->addWidget(registerPage);
    stack->addWidget(forgotPasswordPage);

    setCentralWidget(stack);

    connect(loginPage,
            &LoginPage::openRegisterPage,
            this,
            [this]()
            {
                stack->setCurrentWidget(registerPage);
            });

    connect(registerPage,
            &RegisterPage::openLoginPage,
            this,
            [this]()
            {
                stack->setCurrentWidget(loginPage);
            });

    connect(loginPage,
            &LoginPage::openForgotPasswordPage,
            this,
            [this]()
            {
                stack->setCurrentWidget(forgotPasswordPage);
            });

    connect(forgotPasswordPage,
            &ForgotPasswordPage::openLoginPage,
            this,
            [this]()
            {
                stack->setCurrentWidget(loginPage);
            });
    connect(loginPage,
            &LoginPage::loginSuccessful,
            this,
            [this]()
            {
                QMessageBox::information(this,
                                         "Game",
                                         "Main Menu will open here.");
            });

    stack->setCurrentWidget(loginPage);

    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

