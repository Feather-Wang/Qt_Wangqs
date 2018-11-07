#include "mainwindow.h"
#include <QApplication>

#include <QDockWidget>
#include <QTextEdit>
#include <QPushButton>

/*
 * 停靠区域：类QDockWidget
 * 通过将要停靠的窗口部件，添加到QDockWidget对象上，然后再将QDockWidget对象添加上MainWidow对象上的某个位置上，添加到QDockWidget类中的窗口部件都是浮动的，通过鼠标可以进行移动。
 * MainWindow上可以进行停靠的区域有8个，分别为：左区域、右区域、上区域、下区域、左上区域、右上区域、左下区域、右下区域。其中左上、右上、左下、右下四个角，可以属于两个相邻停靠区域中的任何一个。假如，我们需要让左上角属于左侧的停靠区域，则只需要调用QMainWindow::setCorner( Qt::TopLeftCorner, Qt::LeftDockWidgetArea )即可。
 *
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    QTextEdit *text = new QTextEdit("texttext");
    /*创建停靠区域对象*/
    QDockWidget *firstDockWidget = new QDockWidget("First");
    /*设置停靠区域的名字*/
    firstDockWidget->setObjectName("firstDockWidget");
    /*设置要停靠的窗口部件*/
    firstDockWidget->setWidget(text);
    /*允许停靠的位置，表示这个停靠区域对象，可以停靠在左区域和右区域*/
    firstDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea );
    /*将firstDockWidget对象添加到右区域中*/
    w.addDockWidget(Qt::RightDockWidgetArea, firstDockWidget);
    /*button是QMainWindow窗体上的一个按键，当点击button的时候，显示停靠区域*/
    QObject::connect(w.button, SIGNAL(clicked(bool)), firstDockWidget, SLOT(show()));
    /*显示QMainWindow窗体*/
    w.show();

    return a.exec();
}
