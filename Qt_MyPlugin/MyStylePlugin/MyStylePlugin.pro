#-------------------------------------------------
#
# Project created by QtCreator 2017-03-30T20:45:08
#
#-------------------------------------------------

# ��ʹ��QStylePlugin�࣬��Ҫ����widgets
QT       += core gui widgets
# ָ����Ŀ�������ȥ��������չ����ǰ׺���߰汾��֮��Ļ�����
TARGET = MyStylePlugin
# Ĭ������£�.pro�ļ�ʹ��appģ�壬��������������ָ��Ϊlibģ�壬������Ϊ���ֻ��һ���⣬������һ���ɵ������е�Ӧ�ó���
TEMPLATE = lib
# CONFIG�����Qt������ⲻ��һ��ͨ�ÿ⣬����һ�������
CONFIG += plugin

SOURCES += mystyleplugin.cpp \
    mystyle.cpp

HEADERS += mystyleplugin.h \
    mystyle.h
DISTFILES += \
    MyStylePlugin.json

# DESTDIR�ָ����������Ӧ����ŵ�Ŀ¼��������ݱ��뷽ʽ�ͱ���ƽ̨���������֣�
win32 {
    CONFIG(debug, release|debug):DESTDIR = ../debug/styles/
    CONFIG(release, release|debug):DESTDIR = ../release/styles/
} else {
    DESTDIR = ../styles/
}

target.path = $$[QT_INSTALL_EXAMPLES]/widgets/tools/styleplugin/styles
INSTALLS += target
