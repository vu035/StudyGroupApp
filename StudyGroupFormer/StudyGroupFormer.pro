#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T21:58:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudyGroupFormer
TEMPLATE = app


SOURCES += main.cpp\
        AppWindow.cpp \
<<<<<<< HEAD
        LoginWindow.cpp \
        AllGroups.cpp \
        httpInterface.cpp\
        CreateUser.cpp \
        httpInterface.cpp \
        CreateUser.cpp
=======
    LoginWindow.cpp \
    AllGroups.cpp \
    CreateUser.cpp \
    httpInterface.cpp
    CreateUser.cpp \
    httpInterface.cpp
>>>>>>> b3baa13f5388fb15843e6dab93d47904130713a3

HEADERS  += AppWindow.h \
    LoginWindow.h \
    CreateUser.h \
    HTTPInterface.h

FORMS    += AppWindow.ui \
    LoginWindow.ui \
<<<<<<< HEAD
    CreateUser.ui
=======
    CreateUser.ui\
>>>>>>> b3baa13f5388fb15843e6dab93d47904130713a3
    AllGroups.cpp

HEADERS  += AppWindow.h \
    LoginWindow.h \
    AllGroups.h

FORMS    += AppWindow.ui \
    LoginWindow.ui \
    AllGroups.ui
<<<<<<< HEAD

=======
>>>>>>> b3baa13f5388fb15843e6dab93d47904130713a3
