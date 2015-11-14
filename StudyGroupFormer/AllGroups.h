#ifndef ALLGROUPS_H
#define ALLGROUPS_H

#include <QMainWindow>
#include"AllGroups.h"
#include<iostream>
#include <QString>
#include <QDate>
#include "User.h"

namespace Ui {
class AllGroups;
}

class LoginWindow;
class User;

class AllGroups : public QWidget
{
    Q_OBJECT

public:
    explicit AllGroups(QWidget *parent = 0);
    ~AllGroups();
    void User_Profile();
    void Study_Group_Info();    
    void setColumnsOfTable();

private slots:

    void on_leaveButton_clicked();

    void on_Usergroup_cellClicked(int row, int column);

private:
    Ui::AllGroups *ui;
};

#endif // ALLGROUPS_H
