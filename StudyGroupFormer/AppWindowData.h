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

public:
    AppWindowData();
    QStringList getEnglishCourses();
    QStringList getComputerScienceCourses();
    QStringList getMathCourses();
    void populateEnglishCourses();
    void populateComputerScienceCourses();
    void populateMathCourses();
};

#endif // APPWINDOWDATA

