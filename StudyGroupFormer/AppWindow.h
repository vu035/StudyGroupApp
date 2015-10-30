#ifndef APPWINDOW_H
#define APPWINDOW_H

#include <QMainWindow>
#include"AllGroups.h"
#include<iostream>
#include <QString>
#include <QDate>

namespace Ui {
class AppWindow;
}

class LoginWindow;

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit AppWindow(LoginWindow *login_window);
    void addItemsToComboBox();
    ~AppWindow();

    void setSelectedCourseName();

    void setSelectedCourseNumber();

    void getDateAndTime();

    void setDateAndTime();

private slots:
    void on_createGroup_clicked();

protected:
    Ui::AppWindow *ui;
    LoginWindow *main_login_window;
    AllGroups *main_all_groups_window;
    QString selectedCourseName;
    QString selectedCourseNumber;
    QString dateGroupCreated;
    QString timeGroupCreated;

};

#endif // APPWINDOW_H
