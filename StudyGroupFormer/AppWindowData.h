#ifndef APPWINDOWDATA
#define APPWINDOWDATA
#include <QString>
#include <QWidget>

class AppWindowData
{
private:
    QStringList englishCourses;
    QStringList computerScienceCourses;
    QStringList mathCourses;
    QStringList columnNamesOfTable;
    QStringList courseNameComboBoxList;
    QString noDescriptionForGroupErrorMessage;

public:
    AppWindowData();
    QStringList getEnglishCourses();
    QStringList getComputerScienceCourses();
    QStringList getMathCourses();
    QStringList getColumnNamesOfTable();
    QStringList getCourseNameComboBoxContent();
    QString getGetNoDescriptionForGroupErrorMessage();
    void populateEnglishCourses();
    void populateComputerScienceCourses();
    void populateMathCourses();
    void populateNoDescriptionForGroupErrorMessage();
    void populateColumnNamesOfTable();
    void populateCourseNameComboBox();
};

#endif // APPWINDOWDATA

