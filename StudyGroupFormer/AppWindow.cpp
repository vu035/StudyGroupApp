#include "AppWindow.h"
#include "ui_AppWindow.h"
#include <QThread>

QString m_group_info_id;
const int MAX_NUM_OF_COLUMNS = 4;
const int MAX_NUM_OF_ROWS = 40;

AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::AppWindow)
{
    main_all_groups_window = new AllGroups();
    group_info_window = new GroupInfo(this);
    main_login_window = new LoginWindow(this);
    myAppWindow = new AppWindowData();

    this->setFixedSize(900, 600);

    connect(this, SIGNAL(sendGroupID(QString)), group_info_window, SLOT(setLabelText(QString)));

    ui->setupUi(this);

    addItemsToCourseNameComboBox();
    resetRowCount();
    setColumnsOfTable();

    main_login_window->show();

    QHeaderView* header = ui->listOfAllGroups->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
    web_interface = HTTPInterface::getInstance();

    ui->deleteButton->hide();
    ui->userdeleteButton_2->hide();
    ui->adminprivButton->hide();
    ui->userlistbox->hide();


}

void AppWindow::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn;
    resBtn= QMessageBox::question( this, "Study Group APP",
                                   tr("Are you sure?\n"),
                                   QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                   QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
        QApplication::quit();
    }
}

void AppWindow::addItemsToCourseNameComboBox()
{
    ui->courseNameComboBox->addItems(myAppWindow->getCourseNameComboBoxContent());
}

void AppWindow::setAdminUserDropdown()
{
    QJsonArray userData = web_interface->getAllUsers();
    QStringList UserList;
    foreach (const QJsonValue &value, userData)
    {
        QJsonObject json_obj = value.toObject();
        UserList << QString::number(json_obj["id"].toInt()) +" "+ json_obj["email"].toString() ;
    }
    ui->userlistbox->addItems(UserList);

}

AppWindow::~AppWindow()
{
    delete ui;
    delete main_all_groups_window;
    delete group_info_window;
    delete main_login_window;
}

void AppWindow::setColumnsOfTable()
{
    ui->listOfAllGroups->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listOfAllGroups->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listOfAllGroups->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listOfAllGroups->verticalHeader()->setVisible(false);
    ui->listOfAllGroups->verticalHeader()->font().bold();
    ui->listOfAllGroups->setColumnCount(MAX_NUM_OF_COLUMNS);
    ui->listOfAllGroups->setRowCount(MAX_NUM_OF_ROWS);
    ui->listOfAllGroups->setHorizontalHeaderLabels(myAppWindow->getColumnNamesOfTable());
    ui->listOfAllGroups->setColumnHidden(0, true);
}

void AppWindow::setGroupsVisibleInTable()
{
    QThread::usleep(100);
    QJsonArray groupData = web_interface->getAllGroups();

        ui->listOfAllGroups->setShowGrid(false);
    foreach (const QJsonValue &value, groupData)
    {
        QJsonObject json_obj = value.toObject();
        QString course = json_obj["department"].toString() + " " + QString::number(json_obj["class_number"].toInt());
        ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(QString::number(json_obj["id"].toInt())));
        m_columnCount++;
        ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(course));
        m_columnCount++;
        ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(json_obj["date"].toString()));
        m_columnCount++;
        ui->listOfAllGroups->setItem(m_rowCount,m_columnCount, new QTableWidgetItem(json_obj["time"].toString()));
        m_columnCount=0;
        m_rowCount++;
    }
}

void AppWindow::clearListOfAllGroups()
{
   ui->listOfAllGroups->clear();
}

void AppWindow::on_UserProfile_clicked()
{
    main_all_groups_window->User_Profile();
    main_all_groups_window ->setGeometry(geometry());
    main_all_groups_window->show();
}

void AppWindow::on_successful_login()
{
    ui->usernameLabel->setText(web_interface->getAppUser().m_username);
    if(web_interface->getAppUser().isAdmin == true)
    {
        ui->deleteButton->show();
        ui->userdeleteButton_2->show();
        ui->adminprivButton->show();
        ui->userlistbox->show();
    }
}

void AppWindow::resetRowCount()
{
    m_rowCount=0;
}

void AppWindow::on_getGroupInfo_clicked()
{
    emit sendGroupID(m_group_info_id);
    group_info_window->show();
    while(group_info_window->isVisible()){

        group_info_window->chatPoller();
    }

}

void AppWindow::on_refreshButton_clicked()
{
    resetRowCount();
    clearListOfAllGroups();
    setColumnsOfTable();
    setGroupsVisibleInTable();
}

void AppWindow::on_CreateGroup_clicked()
{

    selectedCourseName = ui->courseNameComboBox->currentText();
    selectedCourseNumber = ui->courseNumberComboBox->currentText();
    dateOfStudyGroup = ui->dateOfStudyWidget->date().toString();
    timeOfStudyGroup = ui->startTimeWidget->time().toString();
    courseDescription = ui->courseDescriptionTextBox->toPlainText().trimmed();

    if(courseDescription == ""|| courseDescription == NULL)
    {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setText(myAppWindow->getGetNoDescriptionForGroupErrorMessage());
        qApp->setQuitOnLastWindowClosed(false);
        messageBox->show();
    }

    else
    {
        qDebug()<< courseDescription;
        web_interface->postCreateGroup(selectedCourseName, selectedCourseNumber, dateOfStudyGroup ,timeOfStudyGroup,courseDescription);
        on_refreshButton_clicked();
        ui->courseDescriptionTextBox->clear();
    }
}

void AppWindow::on_listOfAllGroups_cellClicked(int row)
{
    if(ui->listOfAllGroups->item(row,0) != NULL)
    {
        m_group_info_id = ui->listOfAllGroups->item(row, 0)->text();
    }
}

void AppWindow::on_courseNameComboBox_currentIndexChanged(const QString &itemSelected)
{
    ui->courseNumberComboBox->clear();


    if (QString::compare(itemSelected,"ENGL",Qt::CaseSensitive)==0)
    {
        ui->courseNumberComboBox->addItems(myAppWindow->getEnglishCourses());
    }

    else if(QString::compare(itemSelected,"CS",Qt::CaseSensitive)==0)
    {
        ui->courseNumberComboBox->addItems(myAppWindow->getComputerScienceCourses());
    }

    else if(QString::compare(itemSelected,"MATH",Qt::CaseSensitive)==0)
    {
        ui->courseNumberComboBox->addItems(myAppWindow->getMathCourses());
    }

}

void AppWindow::on_deleteButton_clicked()
{
    web_interface->deleteGroup(m_group_info_id);
    setColumnsOfTable();
    resetRowCount();
    clearListOfAllGroups();
    setGroupsVisibleInTable();
}

void AppWindow::on_userdeleteButton_2_clicked()
{
    web_interface->deleteUser(ui->userlistbox->currentText().split(' ').first());
    setAdminUserDropdown();
}

void AppWindow::on_adminprivButton_clicked()
{
    web_interface->setAdminPrivilege(ui->userlistbox->currentText().split(' ').last());
}
