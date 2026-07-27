/* #ifndef PLAYMENU_H
#define PLAYMENU_H

#include <QMainWindow>

namespace Ui {
class PlayMenu;
}

class PlayMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayMenu(QWidget *parent = nullptr);
    ~PlayMenu();

private:
    Ui::PlayMenu *ui;

signals:
    void backToMenu();

private slots:
    void on_backButton_clicked();
};

#endif  */