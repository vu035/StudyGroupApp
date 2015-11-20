#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include "CreateUser.h"
#include  "User.h"
#include "AllGroups.h"
#include "HTTPInterface.h"

namespace Ui {
class LoginWindow;

}

class HTTPInterface;
class AppWindow;
class CreateUser;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    //explicit LoginWindow(QWidget *parent = 0);
    explicit LoginWindow(AppWindow *main_window);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void on_createButton_clicked();
    void on_password_returnPressed();
    void login();

private:
    Ui::LoginWindow *ui;
    AppWindow *main_app_window;
    CreateUser *create_user_window;
    HTTPInterface *web_interface;
};

#endif // LOGINWINDOW_H
