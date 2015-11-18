#include "HTTPInterface.h"
#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "AppWindow.h"
#include "CreateUser.h"
#include <QDebug>


//LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent),
LoginWindow::LoginWindow(AppWindow *main_window) : QMainWindow(main_window),
    ui(new Ui::LoginWindow)
{

    main_app_window = main_window;
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
    //qDebug() << uname;
    QString pass = ui->password->text();

    //postCreateGroup("CS", "311", "12-20-15", "1:00PM");
    //postCreateUser("1@3", "root", "James", "Hannahan", "JH024");

    //if pass matches encrypted pass, show main window
    if(postLogin(uname, pass)){

        //postJoinGroup("5", getAppUser().m_id);

        //get AppUser's groups from db and set AppUser groups
        getUserGroups(getAppUser());
        //postLeaveGroup("1", getAppUser().m_id);
        //getStudyGroup("1");
        //debug output
        //getAllGroups();





      //hide window
        setVisible(false);
       //hide();
       main_app_window->setGeometry(geometry());
       main_app_window->on_successful_login();
       main_app_window->setGroupsVisibleInTable();
       main_app_window->show();

    }
}

void LoginWindow::on_createButton_clicked()
{
    //hide();
    create_user_window = new CreateUser(this);
    create_user_window->setGeometry(geometry());
    create_user_window->show();
}

void LoginWindow::on_password_returnPressed()
{
    login();
}
