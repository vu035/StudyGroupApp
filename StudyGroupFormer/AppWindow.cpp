#include "AppWindow.h"
#include "ui_AppWindow.h"
#include "LoginWindow.h"

AppWindow::AppWindow(LoginWindow *login_window) :
    QMainWindow(login_window),
    ui(new Ui::AppWindow)
{
    main_login_window = login_window;

    ui->setupUi(this);

}

AppWindow::~AppWindow()
{
    delete ui;
}
