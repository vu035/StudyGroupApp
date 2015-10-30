#include "HTTPInterface.h"
#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "AppWindow.h"
#include "CreateUser.h"
#include <QDebug>

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
   login();
}

void LoginWindow::login(){
    QString uname = ui->username->text();
    qDebug() << uname;
    QString pass = ui->password->text();

    //postCreateGroup("MATH", "360");
    //postCreateUser("root@admin", "root");

    //if pass matches encrypted pass, show main window
    if(postLogin(uname, pass)){

        //debug output
       getAllGroups();

      //hide window
       hide();
       main_app_window->setGeometry(geometry());
       main_app_window->show();

    }
}

void LoginWindow::on_createButton_clicked()
{
    hide();
    create_user_window = new CreateUser(this);
    create_user_window->setGeometry(geometry());
    create_user_window->show();
}

void LoginWindow::on_password_returnPressed()
{
    login();
}
