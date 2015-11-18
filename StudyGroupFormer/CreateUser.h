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

    void on_CreateFirstName_editingFinished();

    void on_CreateLastName_editingFinished();

    void on_CreateUsername_editingFinished();

    void on_CreatePassword_editingFinished();

    void on_CreatePasswordCopy_editingFinished();

    void on_CreateEmail_textEdited(const QString &arg1);

private:
    Ui::CreateUser *ui;
    CreateUser *create_user_window;
};

#endif // CREATEUSER_H
