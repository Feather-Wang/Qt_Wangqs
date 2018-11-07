#-------------------------------------------------
#
# Project created by QtCreator 2017-03-20T21:03:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_Thread
TEMPLATE = app


SOURCES += main.cpp \
    thread.cpp \
    threaddialog.cpp \
    imagewindow.cpp \
    transactionthread.cpp

HEADERS  += \
    thread.h \
    threaddialog.h \
    imagewindow.h \
    transactionthread.h

FORMS +=

RESOURCES += \
    image.qrc
