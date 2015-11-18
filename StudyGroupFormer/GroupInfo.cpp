#include "GroupInfo.h"
#include "ui_GroupInfo.h"

#include "HTTPInterface.h"
#include "AppWindow.h"

GroupInfo::GroupInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupInfo)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    this->adjustSize();
    //displayGroupInfo();
    ui->lstGroupChat->setEnabled(false);
    ui->leGroupMessage->setEnabled(false);
    ui->btnSendMessage->setEnabled(false);
}

void GroupInfo::displayGroupInfo()
{
    //grab the group info
     QJsonObject groupInfo = getStudyGroup("1");
     ui->courseDescription->setEnabled(false);

     //parse the info
     QString groupId = QString::number(groupInfo["id"].toInt());
     QString groupDep = groupInfo["department"].toString();
     QString groupNum = QString::number(groupInfo["class_number"].toInt());
     QString groupCreated = groupInfo["created_at"].toString();
     QString groupUpdated = groupInfo["updated_at"].toString();
     QString groupDate = groupInfo["date"].toString();
     QString groupTime = groupInfo["time"].toString();
     QString groupDescription = groupInfo["description"].toString();

//     qDebug()<<"*********************GROUP DESCRIPTION ****************************";
//     qDebug() << groupDescription;

     ui->lblGID->setText(groupId);
     ui->lblGCName->setText(groupDep + " " + groupNum);
     ui->lblGCreated->setText(groupCreated);
     ui->lblGUpdated->setText(groupUpdated);
     ui->lblGDate->setText(groupDate);
     ui->lblGTime->setText(groupTime);
     ui->courseDescription->setText(groupDescription);
}

void GroupInfo::setLabelText(QString gID)
{
    ui->courseDescription->setEnabled(false);
    QJsonObject groupInfo = getStudyGroup(gID);

    //parse the info
    QString groupId = QString::number(groupInfo["id"].toInt());
    QString groupDep = groupInfo["department"].toString();
    QString groupNum = QString::number(groupInfo["class_number"].toInt());
    QString groupCreated = groupInfo["created_at"].toString();
    QString groupUpdated = groupInfo["updated_at"].toString();
    QString groupDate = groupInfo["date"].toString();
    QString groupTime = groupInfo["time"].toString();
    QString groupDescription = groupInfo["description"].toString();

//    qDebug()<<"*********************GROUP DESCRIPTION ****************************";
//    qDebug() << groupDescription;

    ui->lblGID->setText(groupId);
    ui->lblGCName->setText(groupDep + " " + groupNum);
    ui->lblGCreated->setText(groupCreated);
    ui->lblGUpdated->setText(groupUpdated);
    ui->lblGDate->setText(groupDate);
    ui->lblGTime->setText(groupTime);
    ui->courseDescription->setText(groupDescription);
}

GroupInfo::~GroupInfo()
{
    delete ui;
}

void GroupInfo::on_joinButton_clicked()
{
    ui->lstGroupChat->setEnabled(true);
    ui->leGroupMessage->setEnabled(true);
    ui->btnSendMessage->setEnabled(true);
    postJoinGroup(ui->lblGID->text(),getAppUser().m_id);
}

void GroupInfo::on_btnSendMessage_clicked()
{
    QString myMessage = ui->leGroupMessage->text();
    ui->leGroupMessage->clear();
    qDebug() << myMessage;
}
