#include <QApplication>

#include "tcpclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    TcpClient client;

    return a.exec();
}
