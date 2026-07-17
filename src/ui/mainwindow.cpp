#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "combatpage.h"
#include "entity/ironclad.h"
#include "entity/book_of_stabbing.h"
#include "combat/combat_event.h"
#include "combat/game_action.h"
#include "items/potions/potionfactory.h"
#include "items/relics/relicfactory.h"
#include "combat/manageCombat/combat_manager.h"
#include <QTimer>


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

    stack->setCurrentWidget(loginPage);

    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

