#-------------------------------------------------
#
# Project created by QtCreator 2014-07-13T22:32:32
#
#-------------------------------------------------

QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtKeaz
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    treeitem.cpp \
    treemodel.cpp \
    downloadmanager.cpp \
    maincontroller.cpp

HEADERS  += mainwindow.h \
    treeitem.h \
    treemodel.h \
    downloadmanager.h \
    maincontroller.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

