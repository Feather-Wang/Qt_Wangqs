#-------------------------------------------------
#
# Project created by QtCreator 2017-01-18T22:42:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo_Spreadsheet
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    finddialog.cpp \
    sortialog.cpp \
    usedesignerwindow.cpp \
    spreadsheet.cpp \
    cell.cpp

HEADERS  += mainwindow.h \
    finddialog.h \
    sortdialog.h \
    ui_sortdialog.h \
    ui_useDesignerWindow.h \
    usedesignerwindow.h \
    spreadsheet.h \
    cell.h

FORMS    += mainwindow.ui \
    sortdialog.ui \
    useDesignerWindow.ui

RESOURCES = spreadsheet.qrc
