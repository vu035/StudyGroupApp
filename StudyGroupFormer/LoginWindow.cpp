#include "LoginWindow.h"
#include "ui_LoginWindow.h"
#include "AppWindow.h"
#include "CreateAccountWindow.h"
#include "ui_CreateAccountWindow.h"

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


void LoginWindow::on_pushButton_clicked()
{
    hide();
    main_app_window->show();
}

void LoginWindow::on_pushButton_2_clicked()
{
    New_Account_Window = new CreateAccountWindow(this);
    ui->setupUi(this);

    hide();
    New_Account_Window->show();
}
