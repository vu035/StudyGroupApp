#-------------------------------------------------
#
# Project created by QtCreator 2015-10-07T21:58:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudyGroupFormer
TEMPLATE = app


SOURCES += main.cpp\
        AppWindow.cpp \
    LoginWindow.cpp \
    AllGroups.cpp

HEADERS  += AppWindow.h \
    LoginWindow.h \
    AllGroups.h

FORMS    += AppWindow.ui \
    LoginWindow.ui \
    AllGroups.ui
