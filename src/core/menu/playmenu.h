#ifndef PLAYMENU_H
#define PLAYMENU_H

#include <QMainWindow>

namespace Ui {
class playmenu;
}

class playmenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit playmenu(QWidget *parent = nullptr);
    ~playmenu();

private:
    Ui::playmenu *ui;
};

#endif // PLAYMENU_H
