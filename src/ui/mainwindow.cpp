#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>

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
    leaderboard = new Leaderboard();

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

    setupLeaderboardTable();

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
    delete fileManager;
    delete leaderboard;
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

void MainWindow::setupLeaderboardTable()
{
    ui->leaderboardTable->setColumnCount(5);
    QStringList headers = {"Rank", "Player", "Score", "Games", "Win Rate"};
    ui->leaderboardTable->setHorizontalHeaderLabels(headers);
    ui->leaderboardTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->leaderboardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->leaderboardTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->leaderboardTable->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->leaderboardTable->verticalHeader()->setVisible(false);
    ui->leaderboardTable->setFocusPolicy(Qt::NoFocus);
}

void MainWindow::updateLeaderboardUI()
{
    ui->leaderboardTable->setColumnCount(4);
    QStringList headers;
    headers << "Rank" << "Player Name" << "Highest Score" << "Times Played";
    ui->leaderboardTable->setHorizontalHeaderLabels(headers);

    ui->leaderboardTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->leaderboardTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->leaderboardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    FileManager fileManager;
    const QList<Player> &allPlayers = fileManager.getPlayers();

    int topCount = 10;
    QList<Player> topPlayers = Leaderboard::getTopPlayers(allPlayers, topCount);

    ui->leaderboardTable->setRowCount(0);

    for (int i = 0; i < topPlayers.size(); ++i) {
        const Player &player = topPlayers[i];

        ui->leaderboardTable->insertRow(i);

        QTableWidgetItem *rankItem  = new QTableWidgetItem(QString::number(i + 1));
        QTableWidgetItem *nameItem  = new QTableWidgetItem(player.getUsername());
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(player.getStats().getHighestScore()));
        QTableWidgetItem *gamesItem = new QTableWidgetItem(QString::number(player.getStats().getTimesPlayed()));

        rankItem->setTextAlignment(Qt::AlignCenter);
        nameItem->setTextAlignment(Qt::AlignCenter);
        scoreItem->setTextAlignment(Qt::AlignCenter);
        gamesItem->setTextAlignment(Qt::AlignCenter);

        QColor rowColor;
        if (i == 0) {
            rowColor = QColor(255, 215, 0);
        } else if (i == 1) {
            rowColor = QColor(200, 210, 225);
        } else if (i == 2) {
            rowColor = QColor(220, 140, 80);
        } else {
            rowColor = QColor(235, 220, 180);
        }

        rankItem->setForeground(rowColor);
        nameItem->setForeground(rowColor);
        scoreItem->setForeground(rowColor);
        gamesItem->setForeground(rowColor);

        ui->leaderboardTable->setItem(i, 0, rankItem);
        ui->leaderboardTable->setItem(i, 1, nameItem);
        ui->leaderboardTable->setItem(i, 2, scoreItem);
        ui->leaderboardTable->setItem(i, 3, gamesItem);
    }
}

static void fadeWidget(QWidget *targetWidget, bool show, int durationMs = 300)
{
    if (!targetWidget) return;

    if (show) {
        targetWidget->show();
    }

    QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect(targetWidget);
    targetWidget->setGraphicsEffect(effect);

    QPropertyAnimation *animation = new QPropertyAnimation(effect, "opacity");
    animation->setDuration(durationMs);
    animation->setStartValue(show ? 0.0 : 1.0);
    animation->setEndValue(show ? 1.0 : 0.0);

    QObject::connect(animation, &QPropertyAnimation::finished, [targetWidget, show]() {
        if (!show) {
            targetWidget->hide();
        }
        targetWidget->setGraphicsEffect(nullptr);
    });

    animation->start(QAbstractAnimation::DeleteWhenStopped);
}


void MainWindow::on_playButton_clicked()
{
    fadeWidget(ui->menuFrame, false, 200);
    fadeWidget(ui->darkOverlay, true, 300);
    fadeWidget(ui->playFrame, true, 300);
}

void MainWindow::on_backButton_clicked()
{
    fadeWidget(ui->playFrame, false, 200);
    fadeWidget(ui->darkOverlay, false, 300);
    fadeWidget(ui->menuFrame, true, 300);
}

void MainWindow::on_statisticsButton_clicked()
{
    fadeWidget(ui->menuFrame, false, 200);
    fadeWidget(ui->darkOverlay, true, 300);
    fadeWidget(ui->statisticsFrame, true, 300);
}

void MainWindow::on_backButton_2_clicked()
{
    fadeWidget(ui->statisticsFrame, false, 200);
    fadeWidget(ui->darkOverlay, false, 300);
    fadeWidget(ui->menuFrame, true, 300);
}

void MainWindow::on_leaderBoardButton_clicked()
{
    fadeWidget(ui->statisticsFrame, false, 200);

    updateLeaderboardUI();

    fadeWidget(ui->leaderboardFrame, true, 300);
}

void MainWindow::on_backButton_3_clicked()
{
    fadeWidget(ui->leaderboardFrame, false, 200);
    fadeWidget(ui->statisticsFrame, true, 300);
}

void MainWindow::on_settingsButton_clicked()
{
}

void MainWindow::on_exitButton_clicked()
{
    close();
}