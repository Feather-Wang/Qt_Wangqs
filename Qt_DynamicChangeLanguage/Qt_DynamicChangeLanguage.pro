#-------------------------------------------------
#
# Project created by QtCreator 2017-03-26T23:02:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_DynamicChangeLanguage
TEMPLATE = app


SOURCES += main.cpp \
    dynamicchangelanguage.cpp

HEADERS  += \
    dynamicchangelanguage.h

TRANSLATIONS += language_en.ts \
    language_ja.ts \
    language_zh.ts
