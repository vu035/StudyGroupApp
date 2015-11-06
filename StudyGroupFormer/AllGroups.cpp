#include "AllGroups.h"
#include "ui_AllGroups.h"
#include "LoginWindow.h"
#include "HTTPInterface.h"
#include <QDebug>
#include <QDate>
#include <QString>

AllGroups::AllGroups(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllGroups)
{
    ui->setupUi(this);


}

AllGroups::~AllGroups()
{
    delete ui;
}

void AllGroups::User_Profile(){
    ui->firstnamelabel->setText(getAppUser().m_firstname);
    ui->lastnamelabel->setText(getAppUser().m_lastname);
    ui->usernamelabel->setText(getAppUser().m_username);
    ui->emaillabel->setText(getAppUser().m_email);
}
