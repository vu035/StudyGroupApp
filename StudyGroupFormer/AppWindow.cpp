#include "AppWindow.h"
#include "ui_AppWindow.h"
#include "LoginWindow.h"
#include "HTTPInterface.h"
#include <QDebug>
#include <QDate>
#include <QString>
#include <QSizePolicy>


const int totalNumberOfColumns=3;

AppWindow::AppWindow(LoginWindow *login_window) :
    QMainWindow(login_window),
    ui(new Ui::AppWindow)
{
    main_login_window = login_window;
    this->setFixedSize(800, 700);
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
    setColumnNames<<"Class Name"<<"Date"<<"Time";

    ui->listOfAllGroups->setColumnCount(totalNumberOfColumns);
    ui->listOfAllGroups->setRowCount(1000);
    ui->listOfAllGroups->setHorizontalHeaderLabels(setColumnNames);
}

void AppWindow::setGroupVisibleInTable()
{
    QString course = selectedCourseName + " " + selectedCourseNumber;

    ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(course));
    m_columnCount++;
    ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(dateOfStudyGroup));
    m_columnCount++;
    ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(timeOfStudyGroup));
    m_columnCount=0;
    m_rowCount++;

}

void AppWindow::on_createGroup_clicked()
{
    setDateOfStudyGroup();
    setTimeOfStudyGroup();
    setSelectedCourseName();
    setSelectedCourseNumber();
    setGroupVisibleInTable();
    //postCreateGroup(selectedCourseName, selectedCourseNumber, dateOfStudyGroup, timeOfStudyGroup);

//    qDebug()<<"Number of Row Counter:"<< numberOfRowCounter;
//    qDebug()<<"Row Count:"<< m_rowCount;
//    qDebug()<<"Column Count:"<< m_columnCount;

}

void AppWindow::on_successful_login(){
    ui->usernameLabel->setText(getAppUser().m_username);
    qDebug() << "User has joined the following studygroups:";
    foreach (const QJsonValue &value, getAppUser().m_studygroups) {
        QJsonObject json_obj = value.toObject();
        qDebug() << json_obj["id"].toInt() <<  json_obj["department"].toString() << json_obj["class_number"].toInt() << json_obj["date"].toString() << json_obj["time"].toString();
    }
}
