#include "fileio.h"

#include <QMap>
#include <QString>
#include <QFile>
#include <QDataStream>
#include <QTextStream>
#include <QtDebug>
#include <QImage>

FileIO::FileIO()
{

}


/*
将一个整型数据、一个QImage以及一个QMap存入一个文件
利用了两个类：QFile、QDataStream
*/
void FileIO::fileio_write_binary_file()
{
    QImage image(":/images/image.png");

    QMap<QString, int> map;
    map.insert("red", 1);
    map.insert("green", 2);
    map.insert("blue", 3);

    QString filename("fileio_write_file.dat");
    QFile file(filename);
    if( !file.open(QIODevice::WriteOnly) )
    {
        qDebug() << "file.open error --> [" << filename << "], error info --> " << qPrintable(file.errorString());
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_6);

    out << quint32(0x12345678) << image << map;

    /*这里通过调用flush()检查是否写入成功，如果写入成功，则返回true*/
    if( !file.flush() )
    {
        qDebug() << "file write error";
        return;
    }

    /*这里可以不必明确的关闭文件，当file对象离开它的作用域时，文件会自动关闭*/
    file.close();
}

/*
将fileio_write_file()函数写入的数据，读出来
*/
void FileIO::fileio_read_binary_file()
{
    QImage image;
    QMap<QString, int> map;

    QString filename("fileio_write_file.dat");
    QFile file(filename);
    if( !file.open(QIODevice::ReadOnly) )
    {
        qDebug() << "file.open error --> [" << filename << "], error info --> " << qPrintable(file.errorString());
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_6);
    quint32 n;

    in >> n >> image >> map;

    /*当读取完毕后，可以通过检查状态是不是OK，来判断是否读取成功。除了Ok外，还有两个值：ReadPastEnd、ReadCorruptData*/
    /*如果错误发生，则>>操作符总是取0值或者空值*/
    if( in.status() != QDataStream::Ok )
    {
        qDebug() << "file read error";
    }

    qDebug() << n << map.value("red") << map.value("green");

    /*这里可以不必明确的关闭文件，当file对象离开它的作用域时，文件会自动关闭*/
    file.close();
}


void FileIO::fileio_write_text_file()
{
    QString filename("fileio_text_file.txt");

    QFile file(filename);
    if( !file.open(QIODevice::WriteOnly) )
    {
        qDebug() << "file.open error --> [" << filename << "], error info --> " << qPrintable(file.errorString());
        return;
    }

    QTextStream out(&file);

    out << 12 << " " << "wangqingsong";

    /*这里通过调用flush()检查是否写入成功，如果写入成功，则返回true*/
    if( !file.flush() )
    {
        qDebug() << "file write error";
        return;
    }

    /*这里可以不必明确的关闭文件，当file对象离开它的作用域时，文件会自动关闭*/
    file.close();
}

void FileIO::fileio_read_text_file()
{
    QString str1;
    QString str2;

    QString filename("fileio_text_file.txt");
    QFile file(filename);
    if( !file.open(QIODevice::ReadOnly) )
    {
        qDebug() << "file.open error --> [" << filename << "], error info --> " << qPrintable(file.errorString());
        return;
    }

    QTextStream in(&file);

    in >> str1 >> str2;

    /*当读取完毕后，可以通过检查状态是不是OK，来判断是否读取成功。除了Ok外，还有两个值：ReadPastEnd、ReadCorruptData*/
    /*如果错误发生，则>>操作符总是取0值或者空值*/
    if( in.status() != QTextStream::Ok )
    {
        qDebug() << "file read error";
    }

    qDebug() << str1 << str2;

    /*这里可以不必明确的关闭文件，当file对象离开它的作用域时，文件会自动关闭*/
    file.close();
}
