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
    this->setFixedSize(600, 600);
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

void AllGroups::Study_Group_Info(){
    QJsonArray studyGroupArray;
    for (int i = 0; i < sizeof(QJsonArray); ++i) {
       //ui->studygroup->addItem(studyGroupArray[i]);
    }
}
