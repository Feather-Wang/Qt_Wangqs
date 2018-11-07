#-------------------------------------------------
#
# Project created by QtCreator 2018-09-12T17:03:29
#
#-------------------------------------------------

# 为了使用QPrinter、QPintDialog等类，需要添加Qt += printsupport
QT       += core gui printsupport

# 为了使用QAxObject、QAxWidget等类，需要添加CONFIG += qaxcontainer，也有QT版本是添加在QT += axcontainer
CONFIG += qaxcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QPrinter_PDF_Word_EXECl_Other
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        printpdf.cpp \
    test_doc.cpp

HEADERS  += printpdf.h \
    test_doc.h
