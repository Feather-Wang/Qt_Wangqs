#include <QApplication>
#include <QTextEdit>
#include <QScrollArea>

/*
 * QScrollArea 滚动区域：通过添加子窗口部件，为子窗口部件，添加水平和垂直的滚动条。
 * setWidget()设置子窗口部件。
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextEdit *text = new QTextEdit("line1\nline2\naaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");

    QScrollArea *scroll = new QScrollArea;
    scroll->setWidget(text);

    /*设置滚动区域的水平滚动条和垂直滚动条的策略为总是可见的，因为默认是只有当显示区域小于子窗口部件的大小时，才会显示滚动条*/
    scroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    scroll->show();

    return a.exec();
}
