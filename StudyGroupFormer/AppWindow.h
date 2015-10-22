#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include"AllGroups.h"
#include<iostream>
using namespace std;

namespace Ui {
class AppWindow;
}

class LoginWindow;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(LoginWindow *login_window);
    ~AppWindow();

private slots:
    void on_createGroup_clicked();

private:
    Ui::AppWindow *ui;
    LoginWindow *main_login_window;
    AllGroups *main_all_groups_window;

};

#endif // APPWINDOW_H
