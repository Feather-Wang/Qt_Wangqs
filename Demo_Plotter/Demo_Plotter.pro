#-------------------------------------------------
#
# Project created by QtCreator 2017-02-05T20:25:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo_Plotter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    plotter.cpp

HEADERS  += mainwindow.h \
    plotter.h

FORMS    += mainwindow.ui

RESOURCES += \
    plotter.qrc
