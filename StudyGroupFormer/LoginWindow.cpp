#include "HTTPInterface.h"
#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "AppWindow.h"
#include "CreateUser.h"
#include <QDebug>
#include <QThread>


//LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent),
LoginWindow::LoginWindow(AppWindow *main_window) : QMainWindow(main_window),
    ui(new Ui::LoginWindow)
{

    main_app_window = main_window;
    ui->setupUi(this);

    QPixmap pix(":/image/StudyGroupPic/StudyGroup.jpg");
    ui->label_pic->setPixmap(pix);
    ui->label_pic->setAttribute(Qt::WA_TranslucentBackground);
    web_interface = HTTPInterface::getInstance();
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
    ui->username->setEnabled(false);
    ui->password->setEnabled(false);

    QString uname = ui->username->text();
    //qDebug() << uname;
    QString pass = ui->password->text();

    //if pass matches encrypted pass, show main window
    if(web_interface->postLogin(uname, pass)){

        web_interface->getUserGroups(web_interface->getAppUser());

      //hide window
        setVisible(false);
       //hide();

       main_app_window->setGeometry(geometry());
       main_app_window->on_successful_login();
       main_app_window->setGroupsVisibleInTable();
       main_app_window->show();
       main_app_window->resetRowCount();
       main_app_window->clearListOfAllGroups();
       main_app_window->setColumnsOfTable();
       main_app_window->setGroupsVisibleInTable();
       main_app_window->setAdminUserDropdown();

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
