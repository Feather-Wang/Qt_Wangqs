#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include <QMutex>

class Thread : public QThread
{
    Q_OBJECT

public:
    Thread();

    void setMessage(const QString &message);
    void stop();

protected:
    void run();

private:
    QString messageStr;
    volatile bool stopped;

    /*互斥锁*/
    QMutex mutex;
};

#endif // THREAD_H
