#-------------------------------------------------
#
# Project created by QtCreator 2017-02-22T14:38:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo_Link
TEMPLATE = app


SOURCES += main.cpp\
        link.cpp \
    node.cpp \
    diagramwindow.cpp \
    propertiesdialog.cpp

HEADERS  += link.h \
    node.h \
    diagramwindow.h \
    propertiesdialog.h

FORMS += \
    propertiesdialog.ui

RESOURCES += \
    resources.qrc
