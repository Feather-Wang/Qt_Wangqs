#include <QApplication>

/*微调框：SpinBox*/

/*SpinBox控件类的头文件*/
#include <QSpinBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*创建SpinBox对象*/
    QSpinBox *w = new QSpinBox();

    /*设置SpinBox的范围*/
    w->setRange(0, 100);

    /*设置SpinBox显示的当前值*/
    w->setValue(35);

    /*显示SpinBox*/
    w->show();

    return a.exec();
}
