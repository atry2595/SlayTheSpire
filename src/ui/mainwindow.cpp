#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    takeCentralWidget();

    ui->darkOverlay->hide();

    ui->menuFrame->show();

    ui->playFrame->hide();
    ui->statisticsFrame->hide();
    ui->leaderboardFrame->hide();

    fileManager = new FileManager();

    loginPage = new LoginPage();
    registerPage = new RegisterPage();
    forgotPasswordPage = new ForgotPasswordPage();

    loginPage->setFileManager(fileManager);
    registerPage->setFileManager(fileManager);
    forgotPasswordPage->setFileManager(fileManager);

    authStack = new QStackedWidget(this);

    authStack->addWidget(loginPage);
    authStack->addWidget(registerPage);
    authStack->addWidget(forgotPasswordPage);

    mainStack = new QStackedWidget(this);

    mainStack->addWidget(authStack);
    mainStack->addWidget(ui->centralwidget);

    setCentralWidget(mainStack);

    mainStack->setCurrentWidget(authStack);

    connect(loginPage,
            &LoginPage::openRegisterPage,
            this,
            [this]()
            {
                registerPage->clearFields();
                authStack->setCurrentWidget(registerPage);
            });

    connect(registerPage,
            &RegisterPage::openLoginPage,
            this,
            [this]()
            {
                loginPage->clearFields();
                authStack->setCurrentWidget(loginPage);
            });

    connect(loginPage,
            &LoginPage::openForgotPasswordPage,
            this,
            [this]()
            {
                forgotPasswordPage->clearFields();
                authStack->setCurrentWidget(forgotPasswordPage);
            });

    connect(forgotPasswordPage,
            &ForgotPasswordPage::openLoginPage,
            this,
            [this]()
            {
                loginPage->clearFields();
                authStack->setCurrentWidget(loginPage);
            });

    connect(loginPage,
            &LoginPage::loginSuccessful,
            this,
            [this]()
            {
                showMainMenu();
                mainStack->setCurrentWidget(ui->centralwidget);
            });

    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showMainMenu()
{
    ui->darkOverlay->hide();

    ui->menuFrame->show();

    ui->playFrame->hide();
    ui->statisticsFrame->hide();
    ui->leaderboardFrame->hide();
}

void MainWindow::on_playButton_clicked()
{
    ui->menuFrame->hide();

    ui->darkOverlay->show();
    ui->playFrame->show();
}

void MainWindow::on_backButton_clicked()
{
    ui->playFrame->hide();

    ui->darkOverlay->hide();
    ui->menuFrame->show();
}

void MainWindow::on_statisticsButton_clicked()
{
    ui->menuFrame->hide();

    ui->darkOverlay->show();
    ui->statisticsFrame->show();
}

void MainWindow::on_backButton_2_clicked()
{
    ui->statisticsFrame->hide();

    ui->darkOverlay->hide();
    ui->menuFrame->show();
}

void MainWindow::on_leaderBoardButton_clicked()
{
    ui->statisticsFrame->hide();

    ui->leaderboardFrame->show();
}

void MainWindow::on_backButton_3_clicked()
{
    ui->leaderboardFrame->hide();

    ui->statisticsFrame->show();
}

void MainWindow::on_exitButton_clicked()
{
    close();
}

void MainWindow::on_settingsButton_clicked()
{
}
