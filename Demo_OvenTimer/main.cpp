#include <QApplication>

#include "oventimer.h"

/*
 * 一个微波炉烤箱时间旋钮的例子
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    OvenTimer *oventimer = new OvenTimer;
    oventimer->show();

    return a.exec();
}
