#include "AllGroups.h"
#include "ui_AllGroups.h"


const int MAX_NUM_OF_COLUMNS = 4;
const int MAX_NUM_OF_ROWS = 40;

QString affiliation_id;

AllGroups::AllGroups(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllGroups)
{
    qApp->setQuitOnLastWindowClosed(false);
    ui->setupUi(this);
    this->setFixedSize(600, 500);
    setColumnsOfTable();
    //set qheaderview to stretch fit qtablewidget
    QHeaderView* header = ui->Usergroup->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);

    profile_group_info_window = new GroupInfo(this);
    //profile_group_info_window->setGeometry(geometry());
    connect(this, SIGNAL(sendProfileGroupID(QString)), profile_group_info_window, SLOT(setLabelText(QString)));
    web_interface = HTTPInterface::getInstance();
}

AllGroups::~AllGroups()
{
    delete ui;
}

void AllGroups::User_Profile(){
    ui->firstnamelabel->setText(web_interface->getAppUser().m_firstname);
    ui->lastnamelabel->setText(web_interface->getAppUser().m_lastname);
    ui->usernamelabel->setText(web_interface->getAppUser().m_username);
    ui->emaillabel->setText(web_interface->getAppUser().m_email);

    Study_Group_Info();
}

void AllGroups::Study_Group_Info(){
    web_interface->getUserGroups(web_interface->getAppUser());
    ui->Usergroup->clearContents();

   int m_rowCount  = 0;
   int m_columnCount = 0;

    QJsonArray QJsonA = web_interface->getAppUser().m_studygroups;

    foreach (const QJsonValue &value, QJsonA)
    {
        QJsonObject json_obj = value.toObject();
        QString course = json_obj["department"].toString() + " " + QString::number(json_obj["class_number"].toInt());
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

void AllGroups::on_leaveButton_clicked()
{
     if (affiliation_id != NULL)
     {
          web_interface->postLeaveGroup(affiliation_id, web_interface->getAppUser().m_id);
          Study_Group_Info();
          qDebug() << web_interface->getAppUser().m_studygroups;
     }
}

void AllGroups::on_Usergroup_cellClicked(int row)
{
    if(ui->Usergroup->item(row,0) != NULL)
    {
    affiliation_id = ui->Usergroup->item(row, 0)->text();
    qDebug() << affiliation_id;
    }

}

void AllGroups::on_showGroupButton_clicked()
{
    emit sendProfileGroupID(affiliation_id);
    profile_group_info_window->show();
    while(profile_group_info_window->isVisible()){

        profile_group_info_window->chatPoller();
    }

}
