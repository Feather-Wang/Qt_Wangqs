#include "mainwindow.h"
#include "projectlistwidget.h"
#include <QApplication>
#include <QHBoxLayout>

/*
拖动操作，是应用程序之间传递数据的有力机制，但是在某些情况下，有可能在执行拖放时并未使用Qt的拖放工具。
如果只是想在一个应用程序的窗口部件中移动数据，通常只要重新实现mousePressEvent()和mouseReleaseEvent()函数就可以了。

该实例实现了两种拖动。
MainWindow：将文件拖动到窗口部件里，然后载入文件内容。
ProjectListWidget：应用程序中，两个ProjectListWidget窗口部件之间的拖动。

拖动操作的识别，需要重写QWidget类中的几个事件：
当拖动的文件，进入窗口部件范围内时，触发该事件
void dragEnterEvent(QDragEnterEvent *event);
当拖动的文件，还在窗口部件范围内时，放开文件，触发该事件
void dropEvent(QDropEvent *event);
当拖动文件，在窗口部件范围内移动时，触发该事件
void dragMoveEvent(QDragMoveEvent *event);
当拖动文件，离开窗口部件范围内时，触发该事件
void dragLeaveEvent(QDragLeaveEvent *event);

对于拖动的对象信息，将会存放在一个QMimeData类中，通过QDragLeaveEvent::mimeData()获取这个类对象。
判断拖动对象的类型：QMimeData::hasFormat(format)，format的值列表可以查看MIME类型
获取拖动对象的绝对路径：QMimeData::urls()，返回的是QList类型，可以存储多个对象的路径，也可以存储一个对象的路径

*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    MainWindow w;
    w.show();
    */

    QWidget w;

    ProjectListWidget *w_one = new ProjectListWidget("w_one");
    ProjectListWidget *w_two = new ProjectListWidget("w_two");
    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(w_one);
    layout->addWidget(w_two);

    w.setLayout(layout);
    w.show();

    return a.exec();
}
