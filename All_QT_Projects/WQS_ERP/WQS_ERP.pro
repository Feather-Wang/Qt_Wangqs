#-------------------------------------------------
#
# Project created by QtCreator 2018-08-29T16:25:57
#
#-------------------------------------------------

QT       += core gui sql axcontainer

# 为了使用QAxObject、QAxWidget等类，需要添加CONFIG += qaxcontainer，当然，有些版本使用的时QT += axcontainer
# CONFIG += qaxcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WQS_ERP
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


SOURCES += main.cpp \
    wqs_erp.cpp \
    stock_change_dialog.cpp \
    wordengine.cpp

HEADERS  += \
    wqs_erp.h \
    stock_change_dialog.h \
    wordengine.h
