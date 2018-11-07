#include "mystyleplugin.h"

#include "mystyle.h"
#include <QtDebug>

MyStylePlugin::MyStylePlugin(QObject *parent) :
    QStylePlugin(parent)
{
}

QStringList MyStylePlugin::keys() const
{
    qDebug() << "keys()";
    QStringList() << "MyStylePlugin";
}

QStyle *MyStylePlugin::create(const QString &key)
{
    qDebug() << "create()" << key;
    if( key.toLower() == "mystyleplugin" )
        return new MyStyle;
    return 0;
}

#if QT_VERSION < 0x050000
/*
Q_EXPORT_PLUGIN2()是一个宏
第一个参数是目标库名字去除任意扩展符、前缀或者版本号之后的基本名，默认情况下，qmake会使用当前路径名称作为基本名，这可以通过修改.pro文件中的TARGET项来替换该名字。
第二个参数是插件的类名。
*/
Q_EXPORT_PLUGIN2(MyStylePlugin, MyStylePlugin)
#endif // QT_VERSION < 0x050000
