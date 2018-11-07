#include "mainwindow.h"
#include <QApplication>
#include "printwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    PrintWindow b;
    b.printHtml(NULL);

    return a.exec();
}
