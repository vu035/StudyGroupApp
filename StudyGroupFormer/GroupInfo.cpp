#include "GroupInfo.h"
#include "ui_GroupInfo.h"


GroupInfo::GroupInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GroupInfo)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    this->adjustSize();
    //displayGroupInfo();
    ui->lstGroupChat->setEnabled(true);
    ui->lstGroupChat->setReadOnly(true);
    ui->leGroupMessage->setEnabled(true);
    ui->btnSendMessage->setEnabled(true);
    QScrollBar *scrollbar = ui->lstGroupChat->verticalScrollBar();
    scrollbar->setValue(scrollbar->maximum());
    //disconnect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    web_interface = HTTPInterface::getInstance();

}

void GroupInfo::displayGroupInfo()
{
    //grab the group info
     QJsonObject groupInfo = web_interface->getStudyGroup("1");
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
    QJsonObject groupInfo = web_interface->getStudyGroup(gID);

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

    updateChatWindow(gID);

}

//get updated chat comments from the DB and append them to the chat window
//
void GroupInfo::updateChatWindow(QString group_id){
    QJsonArray temp = web_interface->getGroupComments(group_id);
     ui->lstGroupChat->clear();
     //iterate throught the json arrayq
    foreach (const QJsonValue &value, temp)
    {
        QJsonObject json_obj = value.toObject();
        QString message = json_obj["user"].toString() + ":  " + json_obj["comment"].toString() + "\n";
        ui->lstGroupChat->insertPlainText(message);
    }
    QTextCursor c = ui->lstGroupChat->textCursor();
    c.movePosition(QTextCursor::End);
    ui->lstGroupChat->setTextCursor(c);
}

//poll the chat logs on a delay and update
//not being used for now, possible use later
void GroupInfo::chatPoller(){
    //delay
   QTime dieTime= QTime::currentTime().addSecs(1);

        while (QTime::currentTime() < dieTime){
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
        }
        qDebug() << "updating";
        updateChatWindow(ui->lblGID->text());

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
    web_interface->postJoinGroup(ui->lblGID->text(),web_interface->getAppUser().m_id);
}

void GroupInfo::on_btnSendMessage_clicked()
{
    QString myMessage = ui->leGroupMessage->text();
    //post the comment
    web_interface->postCreateComment(ui->lblGID->text(), web_interface->getAppUser().m_username, myMessage);
    ui->leGroupMessage->clear();
    //set the chat box to display the new message
    updateChatWindow(ui->lblGID->text());
    qDebug() << myMessage;
}


void GroupInfo::on_chatRefreshButton_clicked()
{
    //pass in the group id label and update chat

    updateChatWindow(ui->lblGID->text());
}

void GroupInfo::on_leGroupMessage_returnPressed()
{
    emit on_btnSendMessage_clicked();

}
