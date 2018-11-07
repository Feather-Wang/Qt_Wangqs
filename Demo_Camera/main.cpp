#include "camera.h"
#include <QApplication>

/*
该demo，展示了如果启动摄像头

完成启动摄像头，并显示在窗口部件中，需要两个类
QCamera：完成对摄像头一些参数的设置，以及启动，属于后台控制
QCameraViewfinder：完成对摄像头获取到的图像的展示。

如果想用这两个类，需要在pro文件中额外添加些信息
QCamera：QT += multimedia
QCameraViewfinder： QT += multimediawidgets
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Camera w;
    w.show();

    return a.exec();
}
