#include "CreateAccountWindow.h"
#include "ui_CreateAccountWindow.h"

CreateAccountWindow::CreateAccountWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccountWindow)
{
    ui->setupUi(this);
}

CreateAccountWindow::~CreateAccountWindow()
{
    delete ui;
}
