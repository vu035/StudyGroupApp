#include "AppWindow.h"
#include "ui_AppWindow.h"
#include "LoginWindow.h"

AppWindow::AppWindow(LoginWindow *login_window) :
    QMainWindow(login_window),
    ui(new Ui::AppWindow)
{
    main_login_window = login_window;
    main_all_groups_window = new AllGroups();

    ui->setupUi(this);
}

AppWindow::~AppWindow()
{
    delete ui;
}

void AppWindow::on_createGroup_clicked()
{
    this->hide();
    main_all_groups_window ->setGeometry(geometry());
    main_all_groups_window->show();
}
