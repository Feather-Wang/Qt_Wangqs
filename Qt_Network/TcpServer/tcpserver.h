#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
class QTcpServer;
class QTcpSocket;

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = 0);

signals:

public slots:
    void acceptConnect();
    void readSocketData();

private:
    QTcpServer *server;
    /*这里只能保存一个客户端连接，如果要保存多个，就不能这么写了*/
    QTcpSocket *client;
};

#endif // TCPSERVER_H
