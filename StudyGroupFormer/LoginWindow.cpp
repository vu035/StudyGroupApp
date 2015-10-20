#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "AppWindow.h"
#include "CreateUser.h"

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

void LoginWindow::on_pushButton_2_clicked()
{
    hide();
    create_user_window = new CreateUser(this);
    create_user_window->setGeometry(geometry());
    create_user_window->show();
}
