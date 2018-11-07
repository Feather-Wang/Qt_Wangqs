#include <QApplication>

#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TcpServer server;

    return a.exec();
}
