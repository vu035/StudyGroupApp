#include "AppWindow.h"
#include "ui_AppWindow.h"
#include <QThread>

QString m_group_info_id;
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
    this->setFixedSize(900, 600);

    connect(this, SIGNAL(sendGroupID(QString)), group_info_window, SLOT(setLabelText(QString)));
    ui->setupUi(this);
    m_rowCount=0;
    addItemsToCourseNameComboBox();
    setColumnsOfTable();
    main_login_window->show();
    //set qheaderview to stretch fit qtablewidget
    QHeaderView* header = ui->listOfAllGroups->horizontalHeader();
    header->setSectionResizeMode(QHeaderView::Stretch);
}

void AppWindow::addItemsToCourseNameComboBox()
{
    QStringList courseNameComboBoxList;
    courseNameComboBoxList << "ENGL" << "MATH"<< "CS";
    ui->courseNameComboBox->addItems(courseNameComboBoxList);
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
    ui->listOfAllGroups->verticalHeader()->font().bold();
    ui->listOfAllGroups->setColumnCount(MAX_NUM_OF_COLUMNS);
    ui->listOfAllGroups->setRowCount(MAX_NUM_OF_ROWS);
    ui->listOfAllGroups->setHorizontalHeaderLabels(setColumnNames);
    ui->listOfAllGroups->setColumnHidden(0, true);
}

void AppWindow::setGroupsVisibleInTable()
{
    QThread::usleep(100);
    QJsonArray groupData = getAllGroups();

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
    ui->usernameLabel->setText(getAppUser().m_username);
    qDebug() << "User has joined the following studygroups:";
    foreach (const QJsonValue &value, getAppUser().m_studygroups)
    {
        QJsonObject json_obj = value.toObject();
        qDebug() << json_obj["id"].toInt() <<  json_obj["department"].toString() << json_obj["class_number"].toInt() << json_obj["date"].toString() << json_obj["time"].toString();

    }
    qDebug() << "end";
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
    courseDescription = ui->courseDescriptionTextBox->toPlainText().trimmed();

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
    if(ui->listOfAllGroups->item(row,0) != NULL)
    {
    m_group_info_id = ui->listOfAllGroups->item(row, 0)->text();
    }
    //emit sendGroupID(ui->listOfAllGroups->item(row, 0)->text());

}

void AppWindow::on_courseNameComboBox_currentIndexChanged(const QString &itemSelected)
{
    ui->courseNumberComboBox->clear();
    qDebug()<<"ITEM CURRENTLY SELECTED";
    qDebug()<<itemSelected;

    if (QString::compare(itemSelected,"ENGL",Qt::CaseSensitive)==0)
    {
        QStringList englishCourses;
        englishCourses<<"100"<<"105"<<"107"<<"115"<<"203"<<"206"
                        <<"211"<<"300A"<<"300B"<<"308A"<<"308B"
                          <<"309A"<<"309B"<<"325"<<"330"<<"331"<<"332"
                          <<"333"<<"310"<<"320"<<"315";
        ui->courseNumberComboBox->addItems(englishCourses);
    }

    else if(QString::compare(itemSelected,"CS",Qt::CaseSensitive)==0)
    {
        QStringList computerScienceCourses;
        computerScienceCourses<<"111"<<"211"<<"231"<<"311"<<"331"<<"421"<<"433"<<"436"<<"441";
        ui->courseNumberComboBox->addItems(computerScienceCourses);
    }

    else if(QString::compare(itemSelected,"MATH",Qt::CaseSensitive)==0)
    {
        QStringList mathCourses;
        mathCourses<<"10"<<"20"<<"22"<<"30"<<"30C"<<"100"<<"110"<<"115"<<"125"
                     <<"132"<<"160"<<"162"<<"200"<<"210"<<"212"<<"242"<<"260"<<"262"
                       <<"264"<<"270"<<"303"<<"304"<<"308"<<"311"<<"311B"<<"314"<<"315"
                         <<"330"<<"340"<<"346"<<"350"<<"362"<<"374"<<"378"<<"390"<<"410"
                           <<"422"<<"430"<<"440"<<"441"<<"442"<<"448"<<"464"<<"470"<<"472"
                             <<"474"<<"480"<<"490"<<"491"<<"495"<<"498A"<<"498B"<<"498C"<<"499A"
                               <<"499B"<<"499C"<<"505"<<"510"<<"520"<<"521"<<"522"<<"523"<<"528"
                                 <<"530"<<"532"<<"534"<<"535"<<"536"<<"537"<<"538"<<"540"<<"541"
                                   <<"542"<<"544"<<"550"<<"552"<<"555"<<"561"<<"563"<<"564"<<"570"
                                     <<"571"<<"620"<<"621"<<"697"<<"699";
        ui->courseNumberComboBox->addItems(mathCourses);
    }

}
