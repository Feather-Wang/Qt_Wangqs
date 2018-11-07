#include <QApplication>

#include "watch.h"

/*
该示例，是一个走针类型的表。
涉及到像素的覆盖、坐标系旋转、状态保存等内容。
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Watch watch;
    watch.show();

    return a.exec();
}
