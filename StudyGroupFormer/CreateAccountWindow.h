#ifndef CREATEACCOUNTWINDOW_H
#define CREATEACCOUNTWINDOW_H

#include <QMainWindow>
#include <QDialog>

namespace Ui {
class CreateAccountWindow;
}

class CreateAccountWindow : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAccountWindow(QWidget *parent = 0);
    ~CreateAccountWindow();

private:
    Ui::CreateAccountWindow *ui;
};

#endif // CREATEACCOUNTWINDOW_H
