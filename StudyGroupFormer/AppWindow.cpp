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


    this->hide();
    main_all_groups_window ->setGeometry(geometry());
    main_all_groups_window->show();
}

void AppWindow::on_successful_login(){
   // ui->usernameLabel->setText(getAppUser().m_username);
};
