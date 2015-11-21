#ifndef CREATEUSER_H
#define CREATEUSER_H

#include <QDialog>
#include "LoginWindow.h"
#include "HTTPInterface.h"
#include "AppWindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QThread>


namespace Ui {
class CreateUser;
}

class HTTPInterface;

class CreateUser : public QDialog
{
    Q_OBJECT

public:
    explicit CreateUser(QWidget *parent = 0);
    ~CreateUser();

private slots:
    void on_CreateAccountButton_clicked();

    void on_CreateFirstName_editingFinished();

    void on_CreateLastName_editingFinished();

    void on_CreateUsername_editingFinished();

    void on_CreatePassword_editingFinished();

    void on_CreatePasswordCopy_editingFinished();

    void on_CreateEmail_textEdited();

    void ChangeStatusBar(int bar);

private:
    Ui::CreateUser *ui;
    CreateUser *create_user_window;
    HTTPInterface *web_interface;
    int BarStatus;
};

#endif // CREATEUSER_H
