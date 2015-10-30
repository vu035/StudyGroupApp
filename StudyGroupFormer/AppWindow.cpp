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

void AppWindow::setDateAndTime()
{
    dateGroupCreated = (QDate::currentDate().toString());
    timeGroupCreated = (QTime::currentTime().toString());
}

void AppWindow::on_createGroup_clicked()
{
//    qDebug() << dateGroupCreated;
//    qDebug() << timeGroupCreated;
    setDateAndTime();
    setSelectedCourseName();
    setSelectedCourseNumber();
    postCreateGroup(selectedCourseName, selectedCourseNumber, dateGroupCreated, timeGroupCreated);

    this->hide();
    main_all_groups_window ->setGeometry(geometry());
    main_all_groups_window->show();
}
