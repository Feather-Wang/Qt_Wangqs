#include <QApplication>

/*Label控件类的头文件*/
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*创建一个文本控件的对象，显示内容为“hello world！”*/
    QLabel *w = new QLabel("hello world!");
    /*显示内容*/
    w->show();
    /*将内容更改为下面的内容*/
    w->setText("<h2><i>Hello</i> "
               "<font color=red>world!</font></h2>");

    return a.exec();
}
