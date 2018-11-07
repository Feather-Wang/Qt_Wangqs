#include "mainwindow.h"
#include <QApplication>
#include <QListWidget>
#include <QHBoxLayout>

/*
 * QListWidget 列表窗口部件
 * 通过addItem()或者其他的函数，可以添加要显示的内容
 * 通过setCurrentRow()函数，可以根据序号设置选中的项，根据添加的顺序分配序号，从0开始
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*添加字符串类型的item*/
    QListWidget *list = new QListWidget;
    list->addItem("list 01");
    list->addItem("list 02");
    list->addItem("list 03");
    list->setCurrentRow(1);

    /*添加QListWidgetItem类型的item*/
    QListWidget *listWidget = new QListWidget;
    listWidget->addItem(new QListWidgetItem(QIcon(QObject::tr(":/images/cut.png")), QObject::tr("cut")));
    listWidget->addItem(new QListWidgetItem(QIcon(QObject::tr(":/images/copy.png")), QObject::tr("copy")));
    listWidget->addItem(new QListWidgetItem(QIcon(QObject::tr(":/images/delete.png")), QObject::tr("delete")));

    /*设置items排列的方式，IconMode为水平排列，默认值是ListMode，垂直排列*/
    listWidget->setViewMode(QListWidget::IconMode);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(list);
    layout->addWidget(listWidget);

    QWidget *w = new QWidget;
    w->setLayout(layout);
    w->show();

    return a.exec();
}
