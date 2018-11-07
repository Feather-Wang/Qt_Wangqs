#include "colornamedialog.h"
#include <QApplication>

/*
该demo，实现了使用QSortFilterProxyModel模型，去过滤其它模型的功能。
Demo组成：
QStringListModel：模型，用于存储字符串列表数据
QListView：视图，显示字符串列表数据
QLineEdit：过滤内容
QComboBox：下拉菜单，保存过滤方式

信号-槽：
信号：QLineEdit文本的内容改变
槽：自定义槽，当QLineEdit的内容发生改变时，触发槽函数，
获取QComboBox内的过滤方式，创建QregExp::PatternSyntax过滤对象，
然后将过滤对象，设置到QSortFilterProxyModel模型中，由QSortFilterProxyModel模型完成对被管理模型QStringListModel模型的过滤操作以及刷新显示。
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ColorNameDialog w;


    w.show();

    return a.exec();
}
