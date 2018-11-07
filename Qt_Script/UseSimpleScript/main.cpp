#include <QApplication>
#include <QtScript/QtScript>
#include <QFile>
#include <QTextStream>
#include <QLabel>

/*
执行Script脚本的步骤
1、将Script脚本的内容，读入一个QString中。
2、创建一个QScriptEngine对象，并设置应用程序相关的功能。
3、执行脚本。
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLabel w;
    /*将Script脚本的内容，读入一个QString中。*/
    QFile file(":/script/test.js");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);

    QString script = in.readAll();

    /*创建一个QScriptEngine对象*/
    QScriptEngine engine;

    /*执行脚本，执行输出结果保存在QScriptValue对象中，如果出错，出错信息也保存在QScriptValue对象中*/
    QScriptValue value = engine.evaluate(script);
    /*从QScriptValue对象中取出结果信息*/
    if( !value.isError() && value.isString() )
    {
        w.setText(value.toString());
    }
    else
    {
        w.setText("script has error or not String");
    }

    w.show();

    return a.exec();
}
