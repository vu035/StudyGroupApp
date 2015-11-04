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

    //postCreateGroup("CS", "311", "12-20-15", "1:00PM");
    //postCreateUser("1@3", "root", "James", "Hannahan", "JH024");

    //if pass matches encrypted pass, show main window
    if(postLogin(uname, pass)){

        //postJoinGroup("5", getAppUser().m_id);

        //get AppUser's groups from db and set AppUser groups
        getUserGroups(getAppUser());

        //debug output
        getAllGroups();





      //hide window
       hide();
       main_app_window->setGeometry(geometry());
       main_app_window->on_successful_login();
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
