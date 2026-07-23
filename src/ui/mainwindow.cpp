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
    ui->leaderboardTable->setRowCount(0);

    QList<Player> allPlayers = fileManager->getPlayers();

    QList<Player> topPlayers = Leaderboard::getTopPlayers(allPlayers, allPlayers.size());

    int row = 0;
    for (const auto& player : topPlayers) {
        ui->leaderboardTable->insertRow(row);

        QString rankText;
        if (row == 0) rankText = "🥇 1";
        else if (row == 1) rankText = "🥈 2";
        else if (row == 2) rankText = "🥉 3";
        else rankText = QString::number(row + 1);

        QTableWidgetItem *rankItem = new QTableWidgetItem(rankText);
        QTableWidgetItem *nameItem = new QTableWidgetItem(player.getUsername());
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(player.getStats().getHighestScore()));
        QTableWidgetItem *gamesItem = new QTableWidgetItem(QString::number(player.getStats().getTimesPlayed()));

        double winRate = player.getStats().getWinRate();
        QTableWidgetItem *winRateItem = new QTableWidgetItem(QString("%1%").arg(winRate, 0, 'f', 1));

        rankItem->setTextAlignment(Qt::AlignCenter);
        nameItem->setTextAlignment(Qt::AlignCenter);
        scoreItem->setTextAlignment(Qt::AlignCenter);
        gamesItem->setTextAlignment(Qt::AlignCenter);
        winRateItem->setTextAlignment(Qt::AlignCenter);

        QColor rowColor;
        if (row == 0) rowColor = QColor(255, 210, 60, 40);      // طلایی
        else if (row == 1) rowColor = QColor(200, 200, 200, 40); // نقره‌ای
        else if (row == 2) rowColor = QColor(205, 127, 50, 40);  // برنزی
        else rowColor = QColor(0, 0, 0, 0);

        if (row < 3) {
            rankItem->setBackground(rowColor);
            nameItem->setBackground(rowColor);
            scoreItem->setBackground(rowColor);
            gamesItem->setBackground(rowColor);
            winRateItem->setBackground(rowColor);
        }

        ui->leaderboardTable->setItem(row, 0, rankItem);
        ui->leaderboardTable->setItem(row, 1, nameItem);
        ui->leaderboardTable->setItem(row, 2, scoreItem);
        ui->leaderboardTable->setItem(row, 3, gamesItem);
        ui->leaderboardTable->setItem(row, 4, winRateItem);

        row++;
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
        targetWidget->setGraphicsEffect(nullptr); // تمیزکاری افکت بعد از اتمام انیمیشن
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