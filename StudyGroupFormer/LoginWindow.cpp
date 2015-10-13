#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "AppWindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    main_app_window = new AppWindow(this);
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}



void LoginWindow::on_loginButton_clicked()
{
    hide();
    main_app_window->setGeometry(geometry());
    main_app_window->show();
}
