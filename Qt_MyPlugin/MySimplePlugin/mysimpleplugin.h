#ifndef MYSIMPLEPLUGIN_H
#define MYSIMPLEPLUGIN_H

#include <QObject>
#include <QtPlugin>
#include "interface.h"

class MySimplePlugin : public QObject, InterFace
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.Examples.InterFace" FILE "MySimplePlugin.json")
    Q_INTERFACES(InterFace)
public:
    explicit MySimplePlugin(QObject *parent = 0);

    QString echo(const QString &message);
};

#endif // MYSIMPLEPLUGIN_H
