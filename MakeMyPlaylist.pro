#-------------------------------------------------
#
# Project created by QtCreator 2017-04-25T10:47:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MakeMyPlaylist
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DataBase/database.cpp \
    mmpservice.cpp \
    DataBase/databaseviewer.cpp \
    DataBase/databaseviewermodel.cpp \
    DataBase/proxymodel.cpp

HEADERS  += mainwindow.h \
    DataBase/database.h \
    mmpservice.h \
    DataBase/databaseviewer.h \
    DataBase/databaseviewermodel.h \
    DataBase/proxymodel.h

FORMS    += mainwindow.ui \
    databaseviewer.ui

DISTFILES += \
    Models/general_design.qmodel \
    Models/database.qmodel
