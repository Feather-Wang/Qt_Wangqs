#include <QApplication>

#include <QStyleFactory>
#include <QPushButton>

#include "usesimplewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create("MyStylePlugin"));
    QPushButton button("button");
    button.show();

    /*该类，演示了如何使应用程序感知插件*/
    UseSimpleWindow simpleWindow;
    simpleWindow.show();

    return a.exec();
}
