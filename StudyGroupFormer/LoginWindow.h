#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>


namespace Ui {
class LoginWindow;
}

class AppWindow;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
    AppWindow *main_app_window;
};

#endif // LOGINWINDOW_H
