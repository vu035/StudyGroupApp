#include "AppWindow.h"
#include "ui_AppWindow.h"
#include "LoginWindow.h"
#include <QDebug>

AppWindow::AppWindow(LoginWindow *login_window) :
    QMainWindow(login_window),
    ui(new Ui::AppWindow)
{
    main_login_window = login_window;
    main_all_groups_window = new AllGroups();
    ui->setupUi(this);

    addItemsToComboBox();
}

void AppWindow::addItemsToComboBox()
{
    QStringList courseNameComboBoxList;
    courseNameComboBoxList << "ENGL" << "MATH"<< "CS";
    ui->courseNameComboBox->addItems(courseNameComboBoxList);

    QStringList courseNumberComboBoxList;
    courseNumberComboBoxList << "101" << "111"<< "211";
    ui->courseNumberComboBox->addItems(courseNumberComboBoxList);
}

AppWindow::~AppWindow()
{
    delete ui;
}

void AppWindow::on_createGroup_clicked()
{

    qDebug() << ui->courseNameComboBox->currentText();
    qDebug() << ui->courseNumberComboBox->currentText();

    this->hide();
    main_all_groups_window ->setGeometry(geometry());
    main_all_groups_window->show();
}
