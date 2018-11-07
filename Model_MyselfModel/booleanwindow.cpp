#include "booleanwindow.h"

#include "BooleanItem.h"
#include "booleanmodel.h"
#include "booleanparser.h"
#include <QLabel>
#include <QLineEdit>
#include <QTreeView>
#include <QGridLayout>
#include <QtDebug>

BooleanWindow::BooleanWindow(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(tr("Boolean expression:"));
    lineEdit = new QLineEdit;

    booleanModel = new BooleanModel(this);

    treeView = new QTreeView;
    treeView->setModel(booleanModel);

    connect(lineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(booleanExpressionChanged(const QString &)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(label, 0, 0);
    layout->addWidget(lineEdit, 0, 1);
    layout->addWidget(treeView, 1, 0, 1, 2);
    setLayout(layout);

    setWindowTitle(tr("Boolean Parser"));
}

/*
通过类BooleanParser，将用户输入的逻辑表达式expr，进行解析，然后存储到BooleanItem数据结构中，BooleanItem实际是一个n叉树。
然后调用自定义模型对象model，通过函数setRootItem，将新生成的数据结构对象存储到模型中，在seRootItem()函数中，会调用beginResetModel()和endResetModel()通知关联的视图（也有可能是调用reset()函数，在reset()函数中，实际也是调用的这两个函数），模型中的数据有变动，需要重新刷新。
*/
void BooleanWindow::booleanExpressionChanged(const QString &expr)
{
    BooleanParser parser;
    BooleanItem *rootItem = parser.parse(expr);

    booleanModel->setRootItem(rootItem);
}
