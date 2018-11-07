#include <QApplication>
#include "circlewait.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CircleWait w;
    w.show();

    return a.exec();
}
