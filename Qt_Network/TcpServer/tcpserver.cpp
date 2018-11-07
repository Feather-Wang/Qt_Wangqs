#include "tcpserver.h"
#include <QtDebug>

#include <QtNetwork/QTcpServer>
#include <QtNetwork/QHostAddress>

#include <QtNetwork/QTcpSocket>

TcpServer::TcpServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer;
    server->listen(QHostAddress::Any, 8080);

    /*当有新的连接时，将会发送newConnection()信号，然后触发自定义的槽*/
    connect(server, SIGNAL(newConnection()), this, SLOT(acceptConnect()));
}

void TcpServer::acceptConnect()
{
    if( server->hasPendingConnections() )
    {
        client = server->nextPendingConnection();
        connect(client, SIGNAL(readyRead()), this, SLOT(readSocketData()));
        if( client->isReadable() )
            qDebug() << "read";
    }
}

void TcpServer::readSocketData()
{
    if( client->isReadable() )
    {
        qDebug() << client->readAll();

        if( client->isWritable() )
        {
            qDebug() << "write";
            char buf[]="HTTP/1.1 200 OK\nDate: Sat, 31 Dec 2005 23:59:59 GMT\nContent-Type: text/html;charset=ISO-8859-1\nContent-Length: 7\n\nhelloaa";

            qDebug() << client->write(buf, strlen(buf));
        }
    }
}
