#include "AppWindowData.h"

AppWindowData::AppWindowData()
{
    populateEnglishCourses();
    populateComputerScienceCourses();
    populateMathCourses();
    populateNoDescriptionForGroupErrorMessage();
    populateColumnNamesOfTable();
}

void AppWindowData::populateEnglishCourses()
{
    englishCourses<<"100"<<"105"<<"107"<<"115"<<"203"<<"206"
                    <<"211"<<"300A"<<"300B"<<"308A"<<"308B"
                      <<"309A"<<"309B"<<"325"<<"330"<<"331"<<"332"
                      <<"333"<<"310"<<"320"<<"315";
}

void AppWindowData::populateComputerScienceCourses()
{
    computerScienceCourses<<"111"<<"211"<<"231"<<"311"<<"331"<<"421"<<"433"<<"436"<<"441";
}

void AppWindowData::populateMathCourses()
{
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
}

void AppWindowData::populateCourseNameComboBox()
{
    courseNameComboBoxList << "ENGL" << "MATH"<< "CS";
}

void AppWindowData::populateNoDescriptionForGroupErrorMessage()
{
    noDescriptionForGroupErrorMessage = "Please enter in a description for your study group.";
}

void AppWindowData::populateColumnNamesOfTable()
{
    columnNamesOfTable<<"ID"<<"Class Name"<<"Date"<<"Time";
}

QStringList AppWindowData::getEnglishCourses()
{
    return englishCourses;
}

QStringList AppWindowData::getComputerScienceCourses()
{
    return computerScienceCourses;
}

QStringList AppWindowData::getMathCourses()
{
    return mathCourses;
}

QString AppWindowData::getGetNoDescriptionForGroupErrorMessage()
{
    return noDescriptionForGroupErrorMessage;
}

QStringList AppWindowData::getColumnNamesOfTable()
{
    return columnNamesOfTable;
}

QStringList AppWindowData::getCourseNameComboBoxContent()
{
    return courseNameComboBoxList;
}
