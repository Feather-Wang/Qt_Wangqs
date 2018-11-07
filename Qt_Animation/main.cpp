#include "animation.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Animation w;
    w.show();

    return a.exec();
}
