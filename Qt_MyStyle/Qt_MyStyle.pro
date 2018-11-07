#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T22:34:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Qt_MyStyle
TEMPLATE = app


SOURCES += \
    main.cpp \
    widgetgallery.cpp \
    mystyle.cpp

HEADERS  += \
    widgetgallery.h \
    mystyle.h

FORMS    +=

RESOURCES += \
    styles.qrc

target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/styles
INSTALLS += target
