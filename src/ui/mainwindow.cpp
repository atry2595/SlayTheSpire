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

    if (ui->personalStatsFrame) {
        ui->personalStatsFrame->hide();
    }

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

    connect(loginPage, &LoginPage::openRegisterPage, this, [this]() {
        registerPage->clearFields();
        authStack->setCurrentWidget(registerPage);
    });

    connect(registerPage, &RegisterPage::openLoginPage, this, [this]() {
        loginPage->clearFields();
        authStack->setCurrentWidget(loginPage);
    });

    connect(loginPage, &LoginPage::openForgotPasswordPage, this, [this]() {
        forgotPasswordPage->clearFields();
        authStack->setCurrentWidget(forgotPasswordPage);
    });

    connect(forgotPasswordPage, &ForgotPasswordPage::openLoginPage, this, [this]() {
        loginPage->clearFields();
        authStack->setCurrentWidget(loginPage);
    });

    connect(loginPage, &LoginPage::loginSuccessful, this, [this]() {
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
    ui->leaderboardTable->setShowGrid(false);
    ui->leaderboardTable->setFrameShape(QFrame::NoFrame);

    ui->leaderboardTable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->leaderboardTable->setFocusPolicy(Qt::NoFocus);
    ui->leaderboardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->leaderboardTable->setColumnCount(4);
    QStringList headers = {"Rank", "Player Name", "Highest Score", "Times Played"};
    ui->leaderboardTable->setHorizontalHeaderLabels(headers);

    ui->leaderboardTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->leaderboardTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->leaderboardTable->verticalHeader()->setVisible(false);

    ui->leaderboardTable->setStyleSheet(R"(
        QTableWidget {
            background-color: transparent;
            gridline-color: transparent;
            border: none;
            outline: none;
            font-size: 18px;
            font-weight: bold;
            color: rgb(235, 220, 180);
        }
        QTableWidget::item {
            border: none;
            padding: 10px;
            border-bottom: 1px solid rgba(235, 220, 180, 0.15);
        }
        QTableWidget::item:hover {
            background-color: transparent;
        }
        QHeaderView {
            background-color: transparent;
        }
        QHeaderView::section {
            background-color: transparent;
            color: rgb(255, 210, 60);
            font-size: 20px;
            font-weight: bold;
            border: none;
            border-bottom: 2px solid rgba(235, 220, 180, 0.4);
            padding: 12px;
            text-align: center;
        }
    )");
}

void MainWindow::updateLeaderboardUI()
{
    const QList<Player>& allPlayers = fileManager->getPlayers();

    int maxCount = 10;
    QList<Player> topPlayers = Leaderboard::getTopPlayers(allPlayers, maxCount);

    ui->leaderboardTable->setRowCount(0);
    ui->leaderboardTable->setRowCount(topPlayers.size());

    for (int i = 0; i < topPlayers.size(); ++i) {
        const Player &player = topPlayers[i];

        QString rankStr =QString::number(i + 1);
        QString username = player.getUsername();
        int highestScore = player.getStats().getHighestScore();
        int timesPlayed = player.getStats().getTimesPlayed();

        QTableWidgetItem *rankItem = new QTableWidgetItem(rankStr);
        QTableWidgetItem *nameItem = new QTableWidgetItem(username);
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(highestScore));
        QTableWidgetItem *timesItem = new QTableWidgetItem(QString::number(timesPlayed));

        rankItem->setTextAlignment(Qt::AlignCenter);
        nameItem->setTextAlignment(Qt::AlignCenter);
        scoreItem->setTextAlignment(Qt::AlignCenter);
        timesItem->setTextAlignment(Qt::AlignCenter);

        QColor rowColor;
        if (i == 0) {
            rowColor = QColor(255, 215, 0);
        } else if (i == 1) {
            rowColor = QColor(210, 210, 210);
        } else if (i == 2) {
            rowColor = QColor(205, 127, 50);
        } else {
            rowColor = QColor(235, 220, 180);
        }

        rankItem->setForeground(rowColor);
        nameItem->setForeground(rowColor);
        scoreItem->setForeground(rowColor);
        timesItem->setForeground(rowColor);

        ui->leaderboardTable->setItem(i, 0, rankItem);
        ui->leaderboardTable->setItem(i, 1, nameItem);
        ui->leaderboardTable->setItem(i, 2, scoreItem);
        ui->leaderboardTable->setItem(i, 3, timesItem);
    }
}

void MainWindow::updatePersonalStatsUI()
{
    if (!fileManager) {
        return;
    }

    Player* currentPlayer = fileManager->getLoggedInPlayer();

    if (!currentPlayer) {
        ui->statsUserLabel->setText("👤 <b>Player:</b> Not Logged In");
        ui->statsEmailLabel->setText("✉ <b>Email:</b> N/A");
        ui->statsDetailsLabel->setText("<h3 style='color: #FF5555; text-align: center;'>Please login first to view your statistics!</h3>");
        return;
    }

    const Stats &stats = currentPlayer->getStats();

    ui->statsUserLabel->setText(QString("👤 <b>Player:</b> <span style='color: #FFD700;'>%1</span>").arg(currentPlayer->getUsername()));
    ui->statsEmailLabel->setText(QString("✉ <b>Email:</b> %1").arg(currentPlayer->getEmail()));

    QString statsHtml = QString(R"(
        <table width='100%' cellspacing='8' cellpadding='4' style='color: #EBE0B4; font-size: 14px;'>
            <tr>
                <td><b>🏆 Highest Score:</b> <span style='color: #00FF7F; font-size: 16px;'><b>%1</b></span></td>
                <td><b>🧗 Highest Floor Reached:</b> <span style='color: #00E5FF;'><b>%2</b></span></td>
            </tr>
            <tr>
                <td colspan='2'><b>🎮 Games Played:</b> %3</td>
            </tr>
            <tr>
                <td><b>🥇 Victories:</b> <span style='color: #55FF55;'>%4</span></td>
                <td><b>💀 Losses:</b> <span style='color: #FF5555;'>%5</span></td>
            </tr>
            <tr>
                <td colspan='2'><b>📊 Win Rate:</b> <span style='color: #E040FB;'><b>%6%</b></span></td>
            </tr>
        </table>
        <hr style='border: 0.5px solid #444455; margin-top: 10px; margin-bottom: 10px;' />
        <h3 style='color: #FFD700; text-align: center;'>⚔ COMBAT RECORDS</h3>
        <table width='100%' cellspacing='6' style='color: #CCCCCC; font-size: 13px;'>
            <tr>
                <td>• Monsters Defeated: <b>%7</b></td>
                <td>• Elites Defeated: <b>%8</b></td>
            </tr>
            <tr>
                <td>• Bosses Defeated: <b>%9</b></td>
                <td>• Total Kills: <b style='color: #FFD700;'>%10</b></td>
            </tr>
        </table>
    )")
                            .arg(stats.getHighestScore())
                            .arg(stats.getHighestFloorReached())
                            .arg(stats.getTimesPlayed())
                            .arg(stats.getTimesWon())
                            .arg(stats.getTimesLost())
                            .arg(QString::number(stats.getWinRate(), 'f', 1))
                            .arg(stats.getMonstersKilled())
                            .arg(stats.getElitesKilled())
                            .arg(stats.getBossesKilled())
                            .arg(stats.getTotalEnemiesKilled());

    ui->statsDetailsLabel->setText(statsHtml);
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

void MainWindow::on_personalStatisticsButton_clicked()
{
    updatePersonalStatsUI();
    fadeWidget(ui->statisticsFrame, false, 200);
    fadeWidget(ui->personalStatsFrame, true, 300);
}

void MainWindow::on_backFromStatsButton_clicked()
{
    fadeWidget(ui->personalStatsFrame, false, 200);
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