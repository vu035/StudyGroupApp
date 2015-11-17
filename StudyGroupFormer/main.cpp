#include "HTTPInterface.h"
//#include "LoginWindow.h"
#include "AppWindow.h"
#include <QApplication>
#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //LoginWindow login;

    //login.show();

    AppWindow main;
    main.hide();

    return a.exec();
}
