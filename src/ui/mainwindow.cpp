#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "map/map.h"
#include <iostream>

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

    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

