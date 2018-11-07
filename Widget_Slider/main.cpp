#include <QApplication>

/*滑块控件*/

/*Slider控件类的头文件*/
#include <QSlider>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*创建Slider控件的对象，参数Qt::Horizontal，表示控件是水平方向*/
    QSlider *w = new QSlider(Qt::Horizontal);
    /*设置Slider控件的范围,0-100*/
    w->setRange(0, 100);
    /*设置Slider控件的当前值*/
    w->setValue(50);

    w->show();

    return a.exec();
}
