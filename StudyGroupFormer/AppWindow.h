#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "GroupInfo.h"
#include "AllGroups.h"
#include "HTTPInterface.h"
#include "LoginWindow.h"
#include "GroupInfo.h"
#include "AllGroups.h"
#include "HTTPInterface.h"


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
    void on_successful_login();

private slots:
    void on_UserProfile_clicked();
    void on_getGroupInfo_clicked();
    void on_refreshButton_clicked();
    void on_listOfAllGroups_cellClicked(int row);
    void on_CreateGroup_clicked();

protected:
    Ui::AppWindow *ui;
    LoginWindow *main_login_window;
    GroupInfo *group_info_window;
    QString selectedCourseName;
    QString selectedCourseNumber;
    QString dateOfStudyGroup;
    QString timeOfStudyGroup;
    QString courseDescription;
    int m_rowCount;
    int m_columnCount;

signals:
    void sendGroupID(QString newID);
};

#endif // APPWINDOW_H
