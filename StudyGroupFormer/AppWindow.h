#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>


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

private:
    Ui::AppWindow *ui;
    LoginWindow *main_login_window;
};

#endif // APPWINDOW_H
