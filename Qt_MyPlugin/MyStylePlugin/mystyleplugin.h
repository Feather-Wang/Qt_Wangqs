#ifndef MYSTYLEPLUGIN_H
#define MYSTYLEPLUGIN_H

#include <QStylePlugin>

class MyStylePlugin : public QStylePlugin
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QStyleFactoryInterface" FILE "MyStylePlugin.json")
#endif // QT_VERSION >= 0x050000

public:
    MyStylePlugin(QObject *parent = 0);
    /*
    每一个插件封装器类，至少都要提供者两个函数：
    keys()会返回一个该插件可以创建的对象列表。
    create()返回一个给定键的对象，该key值必须是keys()函数返回列表中的一个。该函数是继承自QStylePlugin类中的一个虚函数。
    */
    QStringList keys() const;
    QStyle *create(const QString &key);
};

#endif // MYSTYLEPLUGIN_H
