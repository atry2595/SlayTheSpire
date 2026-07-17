#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QMainWindow>

namespace Ui {
class RegisterPage;
}

class RegisterPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterPage(QWidget *parent = nullptr);
    ~RegisterPage();

private:
    Ui::RegisterPage *ui;
};

#endif // REGISTERPAGE_H
