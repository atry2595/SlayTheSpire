#ifndef LEADERBOARDPAGE_H
#define LEADERBOARDPAGE_H

#include <QMainWindow>

namespace Ui {
class leaderboardpage;
}

class leaderboardpage : public QMainWindow
{
    Q_OBJECT

public:
    explicit leaderboardpage(QWidget *parent = nullptr);
    ~leaderboardpage();

private:
    Ui::leaderboardpage *ui;
};

#endif // LEADERBOARDPAGE_H
