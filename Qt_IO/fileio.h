#ifndef FILEIO_H
#define FILEIO_H


class FileIO
{
public:
    FileIO();

    /*
     * 通过QFile和QDataStream读取和写入二进制文件.
     *
    */
    void fileio_read_binary_file();
    void fileio_write_binary_file();

    /*通过QFile和QTextStream读取和写入文本文件*/
    void fileio_read_text_file();
    void fileio_write_text_file();
};

#endif // FILEIO_H
