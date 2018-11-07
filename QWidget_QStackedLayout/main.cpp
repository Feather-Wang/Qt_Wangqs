#include <QApplication>
#include <QStackedLayout>
#include <QPushButton>

/*
 * 分页布局管理器：QStackedLayout
 * 通过addWidget或addLayout将布局或窗口部件添加到QStackedLayout中，每一次添加，都会讲窗口部件或布局管理器放置到新的一页。
 * 通过setCurrenIndex()函数可以设置当前显示的是哪一页，参数为分页序号，根据添加的顺序分配的，从0开始
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPushButton *button01 = new QPushButton("button01");
    QPushButton *button02 = new QPushButton("button02");
    QPushButton *button03 = new QPushButton("button03");

    QStackedLayout *qStackedLayout = new QStackedLayout;
    qStackedLayout->addWidget(button01);
    qStackedLayout->addWidget(button02);
    qStackedLayout->addWidget(button03);

    /*显示序号为2的分页*/
    qStackedLayout->setCurrentIndex(1);

    QWidget *w = new QWidget;
    w->setLayout(qStackedLayout);
    w->show();

    return a.exec();
}
