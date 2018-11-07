#include <QApplication>

#include "fileio.h"
#include "dirscan.h"
#include "processsystemcmd.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*写入和读取二进制文件*/
    FileIO fileIO;
    fileIO.fileio_write_binary_file();
    fileIO.fileio_read_binary_file();

    /*写入和读取文本文件*/
    fileIO.fileio_write_text_file();
    fileIO.fileio_read_text_file();

    /*扫描目录，并过滤出指定的类型的文件*/
    DirScan dir;
    dir.dir_scan("..");

    /*执行外部程序*/
    ProcessSystemCmd cmd;
    cmd.RunSystemCmd();
    cmd.RunSystemCmd2();
    cmd.show();
    return a.exec();
}
