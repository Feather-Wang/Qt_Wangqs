#include "tcpclient.h"
#include <QtDebug>

#include <QtNetwork/QTcpSocket>

TcpClient::TcpClient(QObject *parent) : QObject(parent)
{
    client = new QTcpSocket;
    /*连接服务器，第一个参数可以是IP，也可以是域名，该操作是非阻塞操作，所以要在后面调用waitForConnected()等待*/
    client->connectToHost("192.168.1.111", 80);
    /*等待连接结束，有可能连接成功，也有可能连接失败，超时时间为30秒，默认也为30秒*/
    client->waitForConnected(30000);

    /*判断是否为连接成功*/
    if( client->state() == QTcpSocket::ConnectedState )
    {
        /*连接成功，添加读信号-槽关系*/
        qDebug() << "TcpClient is open";
        connect(client, SIGNAL(readyRead()), this, SLOT(readSocketData()));
        /*发送信息*/
        char buf[] = "hello, this is client";
        client->write(buf, strlen(buf));
    }
    else
    {
        qDebug() << "TcpClient connect error : " << client->state() << "error string : " << client->errorString();
    }
}

void TcpClient::readSocketData()
{
    qDebug() << "TcpClient::readSocketData()";
    if( client->isReadable() )
    {
        qDebug() << client->readAll();
    }
}
