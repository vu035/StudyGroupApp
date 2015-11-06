#include "AppWindow.h"
#include "ui_AppWindow.h"
#include "LoginWindow.h"
#include "HTTPInterface.h"
#include <QDebug>
#include <QDate>
#include <QString>




AppWindow::AppWindow(LoginWindow *login_window) :
    QMainWindow(login_window),
    ui(new Ui::AppWindow)
{
    main_login_window = login_window;
    main_all_groups_window = new AllGroups();

    ui->setupUi(this);

    addItemsToComboBox();
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

void AppWindow::on_createGroup_clicked()
{
    setDateOfStudyGroup();
    setTimeOfStudyGroup();
    setSelectedCourseName();
    setSelectedCourseNumber();
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
};
