#include "CreateUser.h"
#include "ui_CreateUser.h"
#include "LoginWindow.h"
#include "HTTPInterface.h"
#include "AppWindow.h"
#include <QDebug>
#include <QMessageBox>

CreateUser::CreateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUser)
{
    ui->setupUi(this);
}

CreateUser::~CreateUser()
{
    delete ui;
}

void CreateUser::on_CreateAccountButton_clicked()
{
    //put text into variables
    QString uname = ui->CreateUsername->text();
    qDebug() << uname;
    QString pass = ui->CreatePassword->text();
    QString passCopy = ui->CreatePasswordCopy->text();
    QString email = ui->CreateEmail->text();
    QString FirstName = ui->CreateFirstName->text();
    QString LastName = ui->CreateLastName->text();

    //need to reverify the new passwords
    //user inputs two passwords that
    //must match
    if(pass != passCopy)
    {
        qDebug() << "**Passwords did NOT match! Cannot create user.";
        QMessageBox::information(this,tr("Cannot Create User"),tr("Passwords do not match!"));
        return;
    }

    //if the passwords match, create user
    if(pass == passCopy)
    {
        qDebug() << "Passwords Matched, creating user...";
        postCreateUser(email, pass, FirstName, LastName, uname);

        //hide window
        hide();
    }


}
