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
    CreateUser.cpp \
    AllGroups.cpp \
    User.cpp \
    HTTPInterface.cpp \
    GroupInfo.cpp \
    AppWindowData.cpp


HEADERS  += AppWindow.h \
    LoginWindow.h \
    CreateUser.h \
    HTTPInterface.h\
    AllGroups.h \
    User.h \
    GroupInfo.h \
    AppWindowData.h

FORMS    += AppWindow.ui \
    LoginWindow.ui \
    CreateUser.ui \
    AllGroups.ui \
    GroupInfo.ui

RESOURCES += \
    studygrouppic.qrc
