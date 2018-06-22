#-------------------------------------------------
#
# Project created by QtCreator 2018-06-19T22:26:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myTodo-List
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myitem.cpp

HEADERS  += mainwindow.h \
    myitem.h

FORMS    += mainwindow.ui

RESOURCES += \
    myResource.qrc
