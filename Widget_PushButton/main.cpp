#include <QApplication>

/*PushButton控件类的头文件*/
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*创建按键实例，并确定按键名称*/
    QPushButton *button = new QPushButton("quit");

    /*将button按钮的信号（这里使用的是clicked()，也就是点击信号）与槽SLOT相连接，当button发送clicked()信号时，槽就会执行连接时指定的行为，这里指定的行为是a类的quit()方法*/
    /*SIGNAL和SLOT都是宏，是QT语法的一部分*/
    QObject::connect(button, SIGNAL(clicked(bool)), &a, SLOT(quit()));
    button->show();

    return a.exec();
}
