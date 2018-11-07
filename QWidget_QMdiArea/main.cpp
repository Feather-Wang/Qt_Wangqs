#include "mainwindow.h"
#include <QApplication>

#include <QTextEdit>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QDebug>

/*
 * 在Qt中，使用QMdiArea类实现多文档界面
 * 通过将窗口部件添加到QMdiArea类中，可以同时显示多个文档界面
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTextEdit *text01 = new QTextEdit("text 01");
    QTextEdit *text02 = new QTextEdit("text 02");
    QTextEdit *text03 = new QTextEdit("text 03");
    /*添加子窗口部件*/
    w.mdiArea->addSubWindow(text01);
    w.mdiArea->addSubWindow(text02);
    w.mdiArea->addSubWindow(text03);
    /*将子窗口部件按照层叠模式显示*/
    w.mdiArea->cascadeSubWindows();
    /*激活下一个子窗口部件和激活上一个子窗口部件，默认是激活最后一个子窗口部件*/
    //w.mdiArea->activateNextSubWindow();
    //w.mdiArea->activatePreviousSubWindow();

    w.show();

    /*获取当前激活的子窗口部件*/
    QMdiSubWindow *subwindow = w.mdiArea->activeSubWindow();
    /*通过qobject_cast，进行类型转换，然后输出当前激活状态的子窗口部件中的内容*/
    QTextEdit *text_temp = qobject_cast<QTextEdit *>(subwindow->widget());
    qDebug() << text_temp->toPlainText();

    return a.exec();
}
