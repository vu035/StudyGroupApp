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
    QString noDescriptionForGroupErrorMessage;

public:
    AppWindowData();
    QStringList getEnglishCourses();
    QStringList getComputerScienceCourses();
    QStringList getMathCourses();
    QString getGetNoDescriptionForGroupErrorMessage();
    void populateEnglishCourses();
    void populateComputerScienceCourses();
    void populateMathCourses();
    void populateNoDescriptionForGroupErrorMessage();

};

#endif // APPWINDOWDATA

