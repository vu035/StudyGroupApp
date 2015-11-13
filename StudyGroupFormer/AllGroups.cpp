#include "AllGroups.h"
#include "ui_AllGroups.h"
#include "LoginWindow.h"
#include "HTTPInterface.h"
#include <QDebug>
#include <QDate>
#include <QString>

const int MAX_NUM_OF_COLUMNS = 4;
const int MAX_NUM_OF_ROWS = 40;

AllGroups::AllGroups(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllGroups)
{
    ui->setupUi(this);
    //this->setFixedSize(600, 600);
    setColumnsOfTable();
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

    Study_Group_Info();
}

void AllGroups::Study_Group_Info(){
    getUserGroups(getAppUser());

   int m_rowCount  = 0;
   int m_columnCount = 0;

    QJsonArray QJsonA = getAppUser().m_studygroups;

    foreach (const QJsonValue &value, QJsonA)
    {
        QJsonObject json_obj = value.toObject();
        QString course = json_obj["department"].toString() + " " + QString::number(json_obj["class_number"].toInt());
        //qDebug() << json_obj["id"].toInt() <<  json_obj["department"].toString() << json_obj["class_number"].toInt() << json_obj["date"].toString() << json_obj["time"].toString();
        qDebug()<< json_obj["id"].toInt() << course;
        ui->Usergroup->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(QString::number(json_obj["id"].toInt())));
        m_columnCount++;
        ui->Usergroup->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(course));
        m_columnCount++;
        ui->Usergroup->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(json_obj["date"].toString()));
        m_columnCount++;
        ui->Usergroup->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(json_obj["time"].toString()));
        m_columnCount=0;
        m_rowCount++;
    }
}

void AllGroups::setColumnsOfTable()
{
    QStringList setColumnNames;
    setColumnNames<<"ID"<<"Class Name"<<"Date"<<"Time";

    ui->Usergroup->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->Usergroup->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->Usergroup->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->Usergroup->verticalHeader()->setVisible(false);
    ui->Usergroup->setColumnCount(MAX_NUM_OF_COLUMNS);
    ui->Usergroup->setRowCount(MAX_NUM_OF_ROWS);
    ui->Usergroup->setHorizontalHeaderLabels(setColumnNames);
}
