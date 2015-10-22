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
    QString uname = ui->username->text();
    qDebug() << uname;
    QString pass = ui->password->text();
    getRequest();
    //postRequest("MATH", "360");
    //postCreateUser("leeroy@cougars.csusm.edu", "123456");

    //if pass matches encrypted pass, show main window
    if(postLogin(uname, pass)){
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
