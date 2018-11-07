#include <QApplication>

/*
本示例，演示了如何动态改变应用程序的语言系统。
在本示例中，添加一些按钮，通过点击不同的语言，动态的改变按钮上显示的字符串的语言。
*/

#include "dynamicchangelanguage.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    DynamicChangeLanguage w;
    w.show();

    return a.exec();
}
