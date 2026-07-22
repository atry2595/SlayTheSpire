#include "leaderboardpage.h"
#include "ui_leaderboardpage.h"

leaderboardpage::leaderboardpage(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::leaderboardpage)
{
    ui->setupUi(this);
}

leaderboardpage::~leaderboardpage()
{
    delete ui;
}
