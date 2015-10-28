#ifndef CREATEUSER_H
#define CREATEUSER_H

#include <QDialog>

namespace Ui {
class CreateUser;
}

class CreateUser : public QDialog
{
    Q_OBJECT

public:
    explicit CreateUser(QWidget *parent = 0);
    ~CreateUser();

private slots:
    void on_CreateAccountButton_clicked();

private:
    Ui::CreateUser *ui;
    CreateUser *create_user_window;
};

#endif // CREATEUSER_H
