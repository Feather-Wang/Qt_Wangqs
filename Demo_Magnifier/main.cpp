#include "magnifier.h"
#include <QApplication>

/*
该demo，演示了放大镜的功能，也可以是缩小镜的功能。
主要应用知识点：
1、桌面像素的获取
2、应用在桌面的坐标
3、QPixmap对象的局部拷贝

完成的功能
1、通过对QPixmap对象的局部拷贝，然后将其绘制到比其大整数倍（比如2）的矩形中，完成放大整数倍的效果（200%）
2、通过鼠标在应用上的移动，实现应用在桌面上的移动，主要是通过获取鼠标在应用上移动的差值，从而获取应用在桌面上的实际坐标，再通过QWidget::move()进行移动
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Magnifier w;
    w.show();

    return a.exec();
}
