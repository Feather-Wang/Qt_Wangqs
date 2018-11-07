#include "dirscan.h"

#include <QImageReader>
#include <QtDebug>

#include <QDir>

DirScan::DirScan()
{

}


void DirScan::dir_scan(const QString &path)
{
    QDir dir(path);

    /*创建一个文件名过滤器列表，每一个成员都是一个过滤器，这里主要是过滤掉不合适的后缀，过滤器可以包含*或者？这类通配符*/
    QStringList filters;
    foreach (QByteArray format, QImageReader::supportedImageFormats() ) {
        filters += "*." + format;
    }

    /*该循环过滤出文件类型，Files表示普通文件，filters是过滤器列表*/
    foreach (QString file, dir.entryList(filters, QDir::Files)) {
        qDebug() << QFileInfo(dir, file).fileName();
    }

    /*该循环过滤出目录文件，并且递归调用该函数，继续遍历子目录，separator()是当前平台的路径的间隔符*/
    /*Dirs表示目录文件，NoDotAndDotDot表示不包含"."和".."*/
    foreach (QString subDir, dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        QString subDirPath;
        subDirPath = path + QDir::separator() + subDir;
        qDebug() << subDirPath;
        dir_scan(subDirPath);
    }
}
