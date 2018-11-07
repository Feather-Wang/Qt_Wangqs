#include "thread.h"
#include <QtDebug>

Thread::Thread()
{
    stopped = false;
}

void Thread::run()
{
    while( 1 )
    {
        /*请求互斥锁*/
        /*可以超时退出的请求*/
        //mutex.tryLock();
        /*阻塞式请求*/
        mutex.lock();
        if( stopped )
        {
            stopped = false;
            mutex.unlock();
            break;
        }
        /*释放互斥锁*/
        mutex.unlock();
        qDebug() << qPrintable(messageStr);
    }
}

void Thread::stop()
{
    mutex.lock();
    stopped = true;
    mutex.unlock();
}

void Thread::setMessage(const QString &message)
{
    messageStr = message;
}
