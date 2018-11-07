#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T21:25:59
#
#-------------------------------------------------

QT       += core gui
# 指定了目标库名字去除任意扩展符、前缀或者版本号之后的基本名
TARGET = MySimplePlugin
# 默认情况下，.pro文件使用app模板，但是这里必须把它指定为lib模板，这是因为插件只是一个库，而不是一个可单独运行的应用程序
TEMPLATE = lib
# CONFIG项告诉Qt，这个库不是一个通用库，而是一个插件库
CONFIG += plugin

SOURCES += \
    mysimpleplugin.cpp

HEADERS += \
    mysimpleplugin.h \
    interface.h
DISTFILES += MySimplePlugin.json
# DESTDIR项，指定了这个插件应当存放的目录，这里根据编译方式和编译平台进行了区分，
win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/simple/
    CONFIG(release, release|debug):DESTDIR = ../release/simple/
} else {
    DESTDIR = ../simple/
}

target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/simpleplugin/plugins
INSTALLS += target
