#include "buttoncall.h"
#include <QtDebug>

#include <QPushButton>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptEngine>

ButtonCall::ButtonCall(QObject *parent) : QObject(parent)
{

}

void ButtonCall::setText(const QString &text)
{
    qDebug() << "buttonCall::setText()";
    QPushButton *button = qscriptvalue_cast<QPushButton*>(thisObject());
    if( button )
        button->setText(text);
}
