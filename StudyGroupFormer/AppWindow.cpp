#include "AppWindow.h"
#include "ui_AppWindow.h"


const int MAX_NUM_OF_COLUMNS = 4;
const int MAX_NUM_OF_ROWS = 40;

//AppWindow::AppWindow(LoginWindow *login_window) : QMainWindow(login_window),
AppWindow::AppWindow(QWidget *parent) : QMainWindow(parent),
    ui(new Ui::AppWindow)
{

    main_all_groups_window = new AllGroups();

    group_info_window = new GroupInfo(this);
    group_info_window->setGeometry(geometry());


    main_login_window = new LoginWindow(this);


    this->setFixedSize(900, 900);

    connect(this, SIGNAL(sendGroupID(QString)), group_info_window, SLOT(setLabelText(QString)));
    ui->setupUi(this);
    m_rowCount=0;
    addItemsToComboBox();
    setColumnsOfTable();
    main_login_window->show();

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

void AppWindow::setColumnsOfTable()
{
    QStringList setColumnNames;
    setColumnNames<<"ID"<<"Class Name"<<"Date"<<"Time";

    ui->listOfAllGroups->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->listOfAllGroups->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->listOfAllGroups->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->listOfAllGroups->verticalHeader()->setVisible(false);
    ui->listOfAllGroups->setColumnCount(MAX_NUM_OF_COLUMNS);
    ui->listOfAllGroups->setRowCount(MAX_NUM_OF_ROWS);
    ui->listOfAllGroups->setHorizontalHeaderLabels(setColumnNames);
}

void AppWindow::setGroupsVisibleInTable()
{
    QJsonArray groupData = getAllGroups();

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

void AppWindow::on_successful_login(){
    ui->usernameLabel->setText(getAppUser().m_username);
    qDebug() << "User has joined the following studygroups:";
    foreach (const QJsonValue &value, getAppUser().m_studygroups) {
        QJsonObject json_obj = value.toObject();
        qDebug() << json_obj["id"].toInt() <<  json_obj["department"].toString() << json_obj["class_number"].toInt() << json_obj["date"].toString() << json_obj["time"].toString();

    }
    qDebug() << "end";
}

void AppWindow::on_getGroupInfo_clicked()
{
    group_info_window->show();
}

void AppWindow::on_refreshButton_clicked()
{
    m_rowCount=0;
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
    courseDescription = ui->courseDescriptionTextBox->toPlainText();

    if(courseDescription == ""|| courseDescription == NULL)
    {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setText("Please enter in a description for your study group.");
        qApp->setQuitOnLastWindowClosed(false);
        messageBox->show();
    }

    else
    {
        qDebug()<< courseDescription;
        postCreateGroup(selectedCourseName, selectedCourseNumber, dateOfStudyGroup ,timeOfStudyGroup,courseDescription);
        on_refreshButton_clicked();
        ui->courseDescriptionTextBox->clear();
    }
}

void AppWindow::on_listOfAllGroups_cellClicked(int row)
{
    emit sendGroupID(ui->listOfAllGroups->item(row, 0)->text());

}
