#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include "core/login/filemanager.h"
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
    void setFileManager(FileManager *manager);

private slots:
    void on_loginButton_clicked();

private:
    Ui::RegisterPage *ui;
    FileManager *fileManager = nullptr;


signals:
    void openLoginPage();
};

#endif // REGISTERPAGE_H
