#include <QApplication>

/*该demo展示了SpinBOx和Slider这两个控件的联动*/

/*重点：窗口类QWidget、布局类QHBoxLayout*/

/*SpinBox和Slider控件类的头文件*/
#include <QSlider>
#include <QSpinBox>

/*布局管理器类的头文件*/
#include <QHBoxLayout>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget *window = new QWidget;
    /*设置窗口的标题*/
    window->setWindowTitle("Enter your age");

    /*创建SpinBox控件的对象*/
    QSpinBox *qSpin = new QSpinBox();
    /*设置SpinBox控件的取值范围*/
    qSpin->setRange(0, 100);
    /*设置SpinBox控件的当前取值*/
    qSpin->setValue(35);

    /*创建Slider控件的对象，并设置成水平方向*/
    QSlider *qSlider = new QSlider(Qt::Horizontal);
    /*设置Slider控件的取值范围*/
    /*因为要与SpinBox联动，所以这里设置的取值范围和当前值都与SpinBox一样*/
    qSlider->setRange(0, 100);
    /*设置Slider控件的当前取值*/
    qSlider->setValue(35);


    /*将SpinBox控件加入到slot中，当SpinBox控件的值发生变化时，发送信号，使Slider控件也跟着一起改变*/
    QObject::connect(qSpin, SIGNAL(valueChanged(int)), qSlider, SLOT(setValue(int)));
    /*与上一步相同，将Slider控件的值的变化也加入到slot中，使SpinBox控件跟着一起改变*/
    QObject::connect(qSlider, SIGNAL(valueChanged(int)), qSpin, SLOT(setValue(int)));

    /*创建布局管理器对象*/
    QHBoxLayout *layout = new QHBoxLayout;
    /*将SpinBox和Slider控件，加入到布局管理器中*/
    layout->addWidget(qSpin);
    layout->addWidget(qSlider);

    /*让窗口类使用layout布局管理器对象*/
    window->setLayout(layout);

    /*展示窗口*/
    window->show();

    return a.exec();
}
