#include "mysimpleplugin.h"

MySimplePlugin::MySimplePlugin(QObject *parent) : QObject(parent)
{

}

QString MySimplePlugin::echo(const QString &message)
{
    return message;
}
