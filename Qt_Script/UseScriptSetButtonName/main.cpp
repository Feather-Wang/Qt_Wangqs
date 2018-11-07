#include <QPushButton>
#include <QApplication>
#include <QtScript>
#include <QtDebug>

#include "buttoncall.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QScriptEngine engine;

    ButtonCall buttonCall;
    engine.setDefaultPrototype(qMetaTypeId<QPushButton*>(), engine.newQObject(&buttonCall));

    QPushButton button;
    engine.globalObject().setProperty("button", engine.newQObject(&button));

    QFile file(":/scripts/test.js");
    file.open(QIODevice::ReadOnly);
    QScriptValue result = engine.evaluate(file.readAll());
    file.close();
    /*如果脚本不能被求值（例如语法错误），hasUncaughtException()将会返回true*/
    if (engine.hasUncaughtException())
    {
        int lineNo = engine.uncaughtExceptionLineNumber();
        qDebug() << "line" << lineNo << ":" << result.toString();
    }

    button.show();

    return app.exec();
}
