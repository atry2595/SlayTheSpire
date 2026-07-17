#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stack = new QStackedWidget(this);

    loginPage = new LoginPage();
    registerPage = new RegisterPage();

    stack->addWidget(loginPage);
    stack->addWidget(registerPage);


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

    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}
