#ifndef DIRSCAN_H
#define DIRSCAN_H

#include <QString>

class DirScan
{
public:
    DirScan();

    /*采用递归的方式，扫描path目录下的文件，然后过滤出指定的文件*/
    void dir_scan(const QString &path);
};

#endif // DIRSCAN_H
