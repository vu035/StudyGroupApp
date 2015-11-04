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

    QPixmap pix(":/image/StudyGroupPic/StudyGroup.jpg");
    ui->label_pic->setPixmap(pix);
    ui->label_pic->setAttribute(Qt::WA_TranslucentBackground);
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

    //postCreateGroup("MATH", "360", "12-22-15", "3:00PM");
    //postCreateUser("root@admin", "root");

    //if pass matches encrypted pass, show main window
    if(postLogin(uname, pass)){

        //postJoinGroup("4", getAppUser().m_id);

        //get AppUser's groups from db and set AppUser groups
        getUserGroups(getAppUser());

        //debug output
        getAllGroups();





      //hide window
       hide();
       main_app_window->setGeometry(geometry());
       main_app_window->on_successful_login();
       main_app_window->setGroupsVisibleInTable();
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
