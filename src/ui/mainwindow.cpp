#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include "core/setting.h"
#include <QPushButton>
#include <QTimer>
#include "assetsManager/soundmanager.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupButtonHoverEffects();

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

    QFont fnt;
    fnt.setFamily((setting::game_language == language::English)?(Fonts::Cascadia):(Fonts::koodak));

    ui->backButton_3->setFont(fnt);
    ui->leaderboardTitleLabel->setFont(fnt);
    ui->personalStatsFrame->setFont(fnt);
    ui->backFromStatsButton->setFont(fnt);
    ui->statsEmailLabel->setFont(fnt);
    ui->statsUserLabel->setFont(fnt);
    ui->statsDetailsLabel->setFont(fnt);
    ui->statsTitleLabel->setFont(fnt);
    ui->backButton->setFont(fnt);
    ui->multiplayerButton->setFont(fnt);
    ui->singlePlayerButton->setFont(fnt);
    ui->backButton_2->setFont(fnt);
    ui->bookletButton->setFont(fnt);
    ui->leaderBoardButton->setFont(fnt);
    ui->personalStatisticsButton->setFont(fnt);
    ui->exitButton->setFont(fnt);
    ui->playButton->setFont(fnt);
    ui->settingsButton->setFont(fnt);
    ui->statisticsButton->setFont(fnt);

    showFullScreen();
}

MainWindow::~MainWindow()
{
    delete fileManager;
    delete leaderboard;
    delete ui;
}

void MainWindow::setupButtonHoverEffects()
{
    QList<QPushButton*> buttons = this->findChildren<QPushButton*>();

    for (QPushButton* btn : buttons) {
        btn->setAttribute(Qt::WA_Hover, true);
        btn->setAutoDefault(false);
        btn->setDefault(false);
        btn->installEventFilter(this);
    }
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::Enter) {
        QPushButton *button = qobject_cast<QPushButton*>(watched);
        if (button) {
            onButtonHovered();
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::onButtonHovered() {
    soundManager::instance().playSoundEffect(SoundEffect::menuHover);
}

void MainWindow::showMainMenu()
{
    soundManager::instance().playBackMusic(BgMusic::main);
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
        ui->statsUserLabel->setText(tr("Player: Not Logged In"));
        ui->statsEmailLabel->setText(tr("Email: N/A"));
        ui->statsDetailsLabel->setText(tr("Please login first to view your statistics!"));
        return;
    }

    ui->statsUserLabel->setAutoFillBackground(false);
    ui->statsEmailLabel->setAutoFillBackground(false);
    ui->statsDetailsLabel->setAutoFillBackground(false);

    ui->statsUserLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->statsEmailLabel->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->statsDetailsLabel->setAttribute(Qt::WA_TranslucentBackground, true);

    QString labelStyle = "background-color: transparent; background: none; border: none; color: #EBE0B4; font-size: 16px; font-weight: bold;";
    ui->statsUserLabel->setStyleSheet(labelStyle);
    ui->statsEmailLabel->setStyleSheet(labelStyle);
    ui->statsDetailsLabel->setStyleSheet(labelStyle);

    const Stats &stats = currentPlayer->getStats();

    ui->statsUserLabel->setText(tr("Player: <span style='color: #FFD700; font-size: 18px;'>%1</span>").arg(currentPlayer->getUsername()));
    ui->statsEmailLabel->setText(tr("Email: <span style='color: #FFD700; font-size: 18px;'>%1</span>").arg(currentPlayer->getEmail()));

    QString statsText = QString("<div style='font-family: \"%1\"; font-size: 18px;'>")
                            .arg(Fonts::Cascadia) + tr(
                            "<table width='100%' cellpadding='8' cellspacing='0'>"
                            "<tr>"

                            "<td valign='top' width='50%'>"
                            "Highest Score: <span style='color: #FFD700;'>%1</span><br>"
                            "Highest Floor Reached: <span style='color: #FFD700;'>%2</span><br>"
                            "Games Played: <span style='color: #FFD700;'>%3</span><br>"
                            "Victories: <span style='color: #FFD700;'>%4</span><br>"
                            "Losses: <span style='color: #FFD700;'>%5</span><br>"
                            "Win Rate: <span style='color: #FFD700;'>%6%</span>"
                            "</td>"

                            "<td valign='top' width='50%'>"
                            "Monsters Defeated: <span style='color: #FFD700;'>%7</span><br>"
                            "Elites Defeated: <span style='color: #FFD700;'>%8</span><br>"
                            "Bosses Defeated: <span style='color: #FFD700;'>%9</span><br>"
                            "Total Kills: <span style='color: #FFD700;'>%10</span>"
                            "</td>"

                            "</tr>"
                            "</table>"
                            ) + "</div>";

    statsText = statsText
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

    ui->statsDetailsLabel->setText(statsText);

}

static void fadeWidget(QWidget *targetWidget, bool show, int durationMs = 300)
{
    Q_UNUSED(durationMs);

    if (!targetWidget)
        return;

    if (targetWidget->objectName() == "leaderboardFrame" ||
        targetWidget->objectName() == "personalStatsFrame")
    {
        if (show)
            targetWidget->show();
        else
            targetWidget->hide();

        return;
    }

    if (show)
        targetWidget->show();
    else
        targetWidget->hide();

}

void MainWindow::on_playButton_clicked()
{
    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    ui->darkOverlay->hide();

    fadeWidget(ui->menuFrame, false, 200);
    fadeWidget(ui->playFrame, true, 300);

    ui->playFrame->raise();
}

void MainWindow::on_backButton_clicked()
{
    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    ui->darkOverlay->hide();

    fadeWidget(ui->playFrame, false, 200);
    fadeWidget(ui->menuFrame, true, 300);

    ui->menuFrame->raise();
}

void MainWindow::on_statisticsButton_clicked()
{
    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    ui->darkOverlay->hide();

    fadeWidget(ui->menuFrame, false, 200);
    fadeWidget(ui->statisticsFrame, true, 300);

    ui->statisticsFrame->raise();
}
void MainWindow::on_personalStatisticsButton_clicked()
{
    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    updatePersonalStatsUI();

    ui->personalStatsFrame->show();
    ui->personalStatsFrame->raise();

    fadeWidget(ui->statisticsFrame, false, 200);

    fadeWidget(ui->darkOverlay, true, 250);
    ui->darkOverlay->raise();

    ui->personalStatsFrame->raise();
}

void MainWindow::on_backFromStatsButton_clicked()
{
    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    fadeWidget(ui->darkOverlay, false, 250);

    ui->statisticsFrame->show();
    ui->statisticsFrame->raise();

    fadeWidget(ui->statisticsFrame, true, 250);

    ui->personalStatsFrame->hide();
}

void MainWindow::on_backButton_2_clicked()
{
    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    ui->darkOverlay->hide();

    fadeWidget(ui->statisticsFrame, false, 200);
    fadeWidget(ui->menuFrame, true, 300);

    ui->menuFrame->raise();
}

void MainWindow::on_leaderBoardButton_clicked()
{
    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    fadeWidget(ui->statisticsFrame, false, 200);

    ui->darkOverlay->show();
    ui->darkOverlay->raise();

    ui->leaderboardFrame->show();
    ui->leaderboardFrame->raise();

    updateLeaderboardUI();

    fadeWidget(ui->leaderboardFrame, true, 300);
}

void MainWindow::on_backButton_3_clicked()
{
    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);

    fadeWidget(ui->leaderboardFrame, false, 200);

    ui->darkOverlay->hide();

    ui->statisticsFrame->show();
    ui->statisticsFrame->raise();
}

void MainWindow::on_settingsButton_clicked()
{
    soundManager::instance().playSoundEffect(SoundEffect::menuSelect);
}

void MainWindow::on_exitButton_clicked()
{

    soundManager::instance().playSoundEffect(SoundEffect::skinSelect);
    QTimer::singleShot(500, [=](){close();});
}