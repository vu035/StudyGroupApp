#include "CreateUser.h"
#include "ui_CreateUser.h"

CreateUser::CreateUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateUser)
{
    ui->setupUi(this);
    ui->CreateUserProgressBar->setValue(0);
    ui->CreateUserProgressBar->setRange(0,100);

    ui->CreateAccountButton->setEnabled(false);
    ui->CreateUserSuccess->setHidden(true);
    web_interface = HTTPInterface::getInstance();

    BarStatus = 0;
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

    //if the first name field is blank
    if(FirstName.isEmpty())
    {
        QMessageBox::information(this,tr("Cannot Create User"),tr("Please type your First Name."));
        return;
    }

    //if the last name field is blank
    if(LastName.isEmpty())
    {
        QMessageBox::information(this,tr("Cannot Create User"),tr("Please type your Last Name."));
        return;
    }

    //if the username field is blank
    if(uname.isEmpty())
    {
        QMessageBox::information(this,tr("Cannot Create User"),tr("Please type a User Name."));
        return;
    }

    //if the email field is blank
    if(email.isEmpty())
    {
        QMessageBox::information(this,tr("Cannot Create User"),tr("Please enter your email."));
        return;
    }

    //if the password field is blank
    if(pass.isEmpty())
    {
        QMessageBox::information(this,tr("Cannot Create User"),tr("Please enter a Password."));
        return;
    }

    //if the matching password field is blank
    if(passCopy.isEmpty())
    {
        QMessageBox::information(this,tr("Cannot Create User"),tr("Please re-type your Password."));
        return;
    }

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
        web_interface->postCreateUser(email, pass, FirstName, LastName, uname); //create user

        QThread::sleep(2);
        hide();
    }


}

void CreateUser::on_CreateFirstName_editingFinished()
{
    BarStatus = BarStatus + 20;
    ChangeStatusBar(BarStatus);
}


void CreateUser::on_CreateLastName_editingFinished()
{
    BarStatus = BarStatus + 20;
    ChangeStatusBar(BarStatus);
}

void CreateUser::on_CreateUsername_editingFinished()
{
    BarStatus = BarStatus + 10;
    ChangeStatusBar(BarStatus);
}

void CreateUser::on_CreatePassword_editingFinished()
{
    BarStatus = BarStatus + 10;
    ChangeStatusBar(BarStatus);
}

void CreateUser::on_CreatePasswordCopy_editingFinished()
{
    BarStatus = BarStatus + 20;
    ChangeStatusBar(BarStatus);
}

void CreateUser::on_CreateEmail_textEdited()
{
    BarStatus = BarStatus + 20;
    ChangeStatusBar(BarStatus);
    ui->CreateAccountButton->setEnabled(true);
    ui->CreateUserSuccess->setHidden(false);
}

void CreateUser::ChangeStatusBar(int bar)
{
    int value = bar;
    ui->CreateUserProgressBar->setValue(value);
}
