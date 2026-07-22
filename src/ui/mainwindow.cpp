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
    menuPage = new Menu();
    playMenu = new PlayMenu();

    loginPage->setFileManager(fileManager);
    registerPage->setFileManager(fileManager);
    forgotPasswordPage->setFileManager(fileManager);

    stack = new QStackedWidget(this);

    stack->addWidget(loginPage);
    stack->addWidget(registerPage);
    stack->addWidget(forgotPasswordPage);
    stack->addWidget(menuPage);
    stack->addWidget(playMenu);

    setCentralWidget(stack);

    connect(menuPage,
            &Menu::exitGame,
            this,
            &QMainWindow::close);

    connect(loginPage,
            &LoginPage::openRegisterPage,
            this,
            [this]()
            {
                registerPage->clearFields();
                stack->setCurrentWidget(registerPage);
            });

    connect(registerPage,
            &RegisterPage::openLoginPage,
            this,
            [this]()
            {
                loginPage->clearFields();
                stack->setCurrentWidget(loginPage);
            });

    connect(loginPage,
            &LoginPage::openForgotPasswordPage,
            this,
            [this]()
            {
                forgotPasswordPage->clearFields();
                stack->setCurrentWidget(forgotPasswordPage);
            });

    connect(forgotPasswordPage,
            &ForgotPasswordPage::openLoginPage,
            this,
            [this]()
            {
                loginPage->clearFields();
                stack->setCurrentWidget(loginPage);
            });

    connect(loginPage,
            &LoginPage::loginSuccessful,
            this,
            [this]()
            {
                stack->setCurrentWidget(menuPage);
            });

    connect(menu,
            &Menu::openPlayPage,
            this,
            [this]()
            {
                stack->setCurrentWidget(playMenu);
            });

    connect(playMenu,
            &PlayMenu::backToMenu,
            this,
            [this]()
            {
                stack->setCurrentWidget(menu);
            });

    stack->setCurrentWidget(loginPage);

    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

