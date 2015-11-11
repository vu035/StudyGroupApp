#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include"AllGroups.h"
#include "GroupInfo.h"
#include<iostream>
#include <QString>
#include <QDate>
#include "User.h"

namespace Ui {
class AppWindow;
}

class LoginWindow;
class User;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:

    AllGroups *main_all_groups_window;
    explicit AppWindow(LoginWindow *login_window);
    void addItemsToComboBox();
    ~AppWindow();
    void setColumnsOfTable();
    void setGroupsVisibleInTable();
    void clearListOfAllGroups();
    QString getSelectedRow();
    void on_successful_login();

private slots:
    void on_UserProfile_clicked();
    void on_getGroupInfo_clicked();
    void on_refreshButton_clicked();

    void on_CreateGroup_clicked();

protected:
    Ui::AppWindow *ui;
    LoginWindow *main_login_window;
    GroupInfo *group_info_window;
    QString selectedCourseName;
    QString selectedCourseNumber;
    QString dateOfStudyGroup;
    QString timeOfStudyGroup;
    int m_rowCount;
    int m_columnCount;
};

#endif // APPWINDOW_H
