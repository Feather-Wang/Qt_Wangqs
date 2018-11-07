#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T20:55:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UsePluginMain
TEMPLATE = app


SOURCES += main.cpp \
    usesimplewindow.cpp

HEADERS  += \
    usesimplewindow.h

INCLUDEPATH    += ../MySimplePlugin

TARGET     = styleplugin
win32 {
    debug:DESTDIR = ../debug/
    release:DESTDIR = ../release/
} else {
    DESTDIR    = ../
}

target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/styleplugin
target.path += $$[QT_INSTALL_EXAMPLES]/widgets/tools/simpleplugin
INSTALLS += target
