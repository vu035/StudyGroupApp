#include "AppWindow.h"
#include "ui_AppWindow.h"
#include "LoginWindow.h"
#include "GroupInfo.h"
#include "AllGroups.h"
#include "HTTPInterface.h"
#include <QDebug>
#include <QDate>
#include <QString>
#include <QSizePolicy>


const int MAX_NUM_OF_COLUMNS = 4;
const int MAX_NUM_OF_ROWS = 20;

AppWindow::AppWindow(LoginWindow *login_window) :
    QMainWindow(login_window),
    ui(new Ui::AppWindow)
{
    group_info_window = new GroupInfo(this);
    group_info_window->setGeometry(geometry());
    main_all_groups_window = new AllGroups();

    main_login_window = login_window;
    this->setFixedSize(900, 900);
    this->resizeEvent(false);

    ui->setupUi(this);
    m_rowCount=0;
    addItemsToComboBox();
    setColumnsOfTable();
}

void AppWindow::addItemsToComboBox()
{
    QStringList courseNameComboBoxList;
    courseNameComboBoxList << "ENGL" << "MATH"<< "CS";
    ui->courseNameComboBox->addItems(courseNameComboBoxList);

    QStringList courseNumberComboBoxList;
    courseNumberComboBoxList << "101" << "111"<< "211";
    ui->courseNumberComboBox->addItems(courseNumberComboBoxList);
}

AppWindow::~AppWindow()
{
    delete ui;
}

void AppWindow::setSelectedCourseName()
{
    selectedCourseName = ui->courseNameComboBox->currentText();
}

void AppWindow::setSelectedCourseNumber()
{
    selectedCourseNumber = ui->courseNumberComboBox->currentText();
}

void AppWindow::setDateOfStudyGroup()
{
   dateOfStudyGroup = ui->dateOfStudyWidget->date().toString();
}

void AppWindow::setTimeOfStudyGroup()
{
    timeOfStudyGroup = ui->startTimeWidget->time().toString();
}

void AppWindow::setColumnsOfTable()
{
    QStringList setColumnNames;
    setColumnNames<<"ID"<<"Class Name"<<"Date"<<"Time";

    ui->listOfAllGroups->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listOfAllGroups->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listOfAllGroups->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listOfAllGroups->verticalHeader()->setVisible(false);
    ui->listOfAllGroups->setColumnCount(MAX_NUM_OF_COLUMNS);
    ui->listOfAllGroups->setRowCount(MAX_NUM_OF_ROWS);
    ui->listOfAllGroups->setHorizontalHeaderLabels(setColumnNames);
}

void AppWindow::setGroupsVisibleInTable()
{
    QJsonArray groupData = getAllGroups();

    foreach (const QJsonValue &value, groupData)
    {
        QJsonObject json_obj = value.toObject();
        QString course = json_obj["department"].toString() + " " + QString::number(json_obj["class_number"].toInt());
        //qDebug() << json_obj["id"].toInt() <<  json_obj["department"].toString() << json_obj["class_number"].toInt() << json_obj["date"].toString() << json_obj["time"].toString();
        qDebug()<< json_obj["id"].toInt() << course;
        ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(QString::number(json_obj["id"].toInt())));
        m_columnCount++;
        ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(course));
        m_columnCount++;
        ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(json_obj["date"].toString()));
        m_columnCount++;
        ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(json_obj["time"].toString()));
        m_columnCount=0;
        m_rowCount++;
    }
}

QString AppWindow::getSelectedRow()
{
    int selected;
    for(int i=0; i< m_rowCount; i++)
    {
        if(ui->listOfAllGroups->item(i,0)->isSelected()) selected = i+1;
    }
    return (QString)selected;
}

void AppWindow::on_createGroup_clicked()
{
    setDateOfStudyGroup();
    setTimeOfStudyGroup();
    setSelectedCourseName();
    setSelectedCourseNumber();
    qDebug()<<"Selected Row: "<< getSelectedRow();
    postCreateGroup(selectedCourseName, selectedCourseNumber, dateOfStudyGroup, timeOfStudyGroup);

    main_all_groups_window->User_Profile();
    this->hide();
    main_all_groups_window ->setGeometry(geometry());
    main_all_groups_window->show();
}

void AppWindow::on_successful_login(){
    ui->usernameLabel->setText(getAppUser().m_username);
    qDebug() << "User has joined the following studygroups:";
    foreach (const QJsonValue &value, getAppUser().m_studygroups) {
        QJsonObject json_obj = value.toObject();
        qDebug() << json_obj["id"].toInt() <<  json_obj["department"].toString() << json_obj["class_number"].toInt() << json_obj["date"].toString() << json_obj["time"].toString();
    }
}

void AppWindow::on_pushButton_clicked()
{
    group_info_window->show();
    //here we will opne the new window group info
}
