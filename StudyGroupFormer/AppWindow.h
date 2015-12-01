#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "GroupInfo.h"
#include "HTTPInterface.h"
#include "LoginWindow.h"
#include "GroupInfo.h"
#include "AllGroups.h"
#include "AppWindowData.h"


namespace Ui {
class AppWindow;
}

class LoginWindow;
class User;
class HTTPInterface;
class AllGroups;
class GroupInfo;
class AppWindowData;


class AppWindow : public QMainWindow
{
    Q_OBJECT

public:

    AllGroups *main_all_groups_window;
    //explicit AppWindow(LoginWindow *login_window);
    explicit AppWindow(QWidget *parent = 0);
    void addItemsToCourseNameComboBox();
    ~AppWindow();
    void setColumnsOfTable();
    void setGroupsVisibleInTable();
    void clearListOfAllGroups();
    void on_successful_login();
    int getIdOfSelectedRow();
    void resetRowCount();
    void setAdminUserDropdown();

private slots:
    void on_UserProfile_clicked();
    void on_getGroupInfo_clicked();
    void on_refreshButton_clicked();
    void on_listOfAllGroups_cellClicked(int row);
    void on_CreateGroup_clicked();
    void on_courseNameComboBox_currentIndexChanged(const QString &itemSelected);
    void closeEvent (QCloseEvent *event);

    void on_deleteButton_clicked();

    void on_userdeleteButton_2_clicked();

    void on_adminprivButton_clicked();

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
    QStringList englishCourses;
    QStringList mathCourses;
    QStringList computerScienceCourses;
    HTTPInterface *web_interface;
    AppWindowData *myAppWindow;

signals:
    void sendGroupID(QString newID);


};

#endif // APPWINDOW_H
