#include <QApplication>
#include <QSplitter>
#include <QTextEdit>

/*
 * QSplitter 切分窗口：就是一个可以包含其它窗口部件的窗口部件，在切分窗口中的这些窗口部件会通过切分条而分隔开，
 * 用户可以通过拖动切分条来改变切分窗口中子窗口部件的大小。切分窗口常常可以用作布局管理器的替代品，从而可以把更多的控制权交给用户。
 * 构造函数的参数，可以指定子窗口部件的排列的方式：水平Qt::Horizontal或者垂直Qt:Vertical
 * 通过addWidget()添加子窗口部件。
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextEdit *text01 = new QTextEdit("textEdit 01");
    QTextEdit *text02 = new QTextEdit("textEdit 02");
    QTextEdit *text03 = new QTextEdit("textEdit 03");

    QSplitter *splitter = new QSplitter(Qt::Horizontal);
    splitter->addWidget(text01);
    splitter->addWidget(text02);
    splitter->addWidget(text03);
    /*设置切分窗口的子窗口部件的拉伸因子，第一个参数是指定的子窗口部件的序号，第二个参数是拉伸参数。
     * 因为这里只是设置了第二个子窗口部件的拉伸因子是1，而其余的窗口部件是默认值0，所以拉伸时，其它窗口部件的大小将不会改变。
    */
    splitter->setStretchFactor(1, 1);
    splitter->saveState();

    splitter->show();

    return a.exec();
}
