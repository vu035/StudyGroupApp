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
    LoginWindow.cpp \
<<<<<<< HEAD
    CreateUser.cpp \
    httpInterface.cpp

HEADERS  += AppWindow.h \
    LoginWindow.h \
    CreateUser.h \
    HTTPInterface.h

FORMS    += AppWindow.ui \
    LoginWindow.ui \
    CreateUser.ui
=======
    AllGroups.cpp

HEADERS  += AppWindow.h \
    LoginWindow.h \
    AllGroups.h

FORMS    += AppWindow.ui \
    LoginWindow.ui \
    AllGroups.ui
>>>>>>> AndrewVuDev
