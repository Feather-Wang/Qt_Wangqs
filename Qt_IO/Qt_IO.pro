#-------------------------------------------------
#
# Project created by QtCreator 2017-03-14T20:47:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_IO
TEMPLATE = app


SOURCES += main.cpp \
    fileio.cpp \
    dirscan.cpp \
    processsystemcmd.cpp

HEADERS  += \
    fileio.h \
    dirscan.h \
    processsystemcmd.h

RESOURCES += \
    images.qrc
