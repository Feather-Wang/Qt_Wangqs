#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T20:45:08
#
#-------------------------------------------------

# 想使用QStylePlugin类，需要加上widgets
QT       += core gui widgets
# 指定了目标库名字去除任意扩展符、前缀或者版本号之后的基本名
TARGET = MyStylePlugin
# 默认情况下，.pro文件使用app模板，但是这里必须把它指定为lib模板，这是因为插件只是一个库，而不是一个可单独运行的应用程序
TEMPLATE = lib
# CONFIG项告诉Qt，这个库不是一个通用库，而是一个插件库
CONFIG += plugin

SOURCES += mystyleplugin.cpp \
    mystyle.cpp

HEADERS += mystyleplugin.h \
    mystyle.h
DISTFILES += \
    MyStylePlugin.json

# DESTDIR项，指定了这个插件应当存放的目录，这里根据编译方式和编译平台进行了区分，
win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/styles/
    CONFIG(release, release|debug):DESTDIR = ../release/styles/
} else {
    DESTDIR = ../styles/
}

target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/styleplugin/styles
INSTALLS += target
