#include <QApplication>

#include "plotter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Plotter *p = new Plotter;
    p->show();

    return a.exec();
}
