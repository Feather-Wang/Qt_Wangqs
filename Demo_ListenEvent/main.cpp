#include <QApplication>
#include "listenevent.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ListenEvent *listenEvent = new ListenEvent;
    listenEvent->show();

    return a.exec();
}
