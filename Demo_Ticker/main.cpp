
#include <QApplication>
#include "ticker.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ticker *ticker = new Ticker;
    ticker->setText("wangqingsong is hello world!");
    ticker->show();

    return a.exec();
}
