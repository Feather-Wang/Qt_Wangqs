#include "personlist.h"

#include <QStringListModel>
#include <QListView>

PersonList::PersonList(QWidget *parent)
    :QWidget(parent)
{
    QStringList persons;
    persons.append("wangqingsong");
    persons.append("wangyuxiang");
    persons.append("wangxinyu");

    /*创建一个QStringListModel模型*/
    model = new QStringListModel;
    /*设置这个模型管理的字符串列表*/
    model->setStringList(persons);

    /*创建一个QListVIew对象*/
    listView = new QListView(this);
    /*设置listView关联的模型为之前创建的QStringListModel模型*/
    listView->setModel(model);
    /*设置了编辑触发器，可以通过任何按键或者双击进入编辑字符串的状态
    默认情况下，QListView中没有任何编辑触发器，这样就使这个视图只读
    */
    listView->setEditTriggers(QAbstractItemView::EditKeyPressed | QAbstractItemView::DoubleClicked );

    /*不知道为什么，如果不这么设置策略，当程序启动时，listView会没有显示*/
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

PersonList::~PersonList()
{

}

/*
槽函数。
当用户单机insert按钮的时候，insert()槽就会得到调用。
首先获取列表视图的当前项的行数。
在QStringListModel中，每一个数据项都对应一个“模型索引”，它是由一个QModelIndex对象表示的。
一个模型索引由三部分构成：行、列、所属模型的指针
*/
void PersonList::insert()
{
    int row = listView->currentIndex().row();
    /*row是插入的行数，1表示数量*/
    model->insertRows(row, 1);

    /*获取插入的行数的模型索引，将新插入的行设置为选中状态，然后进入编辑状态*/
    QModelIndex index = model->index(row);
    listView->setCurrentIndex(index);
    listView->edit(index);

    qDebug("row = %d, index = %d\n", row, index.row());
}

/*从模型中移除第一个参数所代表的行数，数量是1*/
void PersonList::del()
{
    qDebug("row = %d\n", listView->currentIndex().row());
    model->removeRows(listView->currentIndex().row(), 1);
}

/*返回模型中的字符串列表*/
QStringList PersonList::persons() const
{
    return model->stringList();
}
