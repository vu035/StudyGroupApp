#include "HTTPInterface.h"
#include "LoginWindow.h"
#include <QApplication>
#include <QCoreApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow login;

    login.show();
  QJsonArray response = getRequest();


    return a.exec();
}
