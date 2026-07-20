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
    void clearFields();

private slots:
    void on_loginButton_clicked();

    void on_signUpButton_clicked();

private:
    Ui::RegisterPage *ui;
    FileManager *fileManager = nullptr;

    void setUsernameNormalStyle();
    void setUsernameErrorStyle();


signals:
    void openLoginPage();
};

#endif // REGISTERPAGE_H
