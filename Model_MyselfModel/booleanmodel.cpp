#include "booleanmodel.h"
#include "BooleanItem.h"
#include <QtDebug>

BooleanModel::BooleanModel(QObject *parent)
    :QAbstractItemModel(parent)
{
    rootItem = 0;
}

/*删除根项*/
BooleanModel::~BooleanModel()
{
    delete rootItem;
}

/*
存储模型保存的数据，然后调用beginResetModel()和endResetModel()，通知所有视图，它们必须为任何一个可见的项重新获取数据。也可以调用reset()，有些Qt版本不支持reset()，在reset()中实际也是调用的beginResetModel()和endResetModel()
*/
void BooleanModel::setRootItem(BooleanItem *item)
{
    delete rootItem;
    rootItem = item;
    //reset();
    beginResetModel();
    endResetModel();
}

/*
当模型或者试图需要为一个特定的项创建一个QModelIndex的时候，这个函数就会被调用。对于表模型和列表模型，不需要重新实现该函数，因为QAbstractTableModel和QAbstractListModel默认的实现已经足够了。
在index()实现中，如果没有设置解析树，就会返回一个无效的QModelIndex。
否则，就根据给定的行和列以及一个BooleanItem *创建一个QModelIndex。
对于层次模型，已知一个项相对于它的父对象的行和列并不能够唯一确定它，还必须知道它的父对象是谁。
为了解决这个问题，可以在QModelIndex中存储一个指向内部节点的指针。
除了行号和列号外，QModelIndex还为我们提供了存储一个void *或者int的选择。
*/
QModelIndex BooleanModel::index(int row, int column, const QModelIndex &parent) const
{
    if( !rootItem || row < 0 || column < 0 )
    {
        return QModelIndex();
    }

    BooleanItem *parentItem = itemFromIndex(parent);
    BooleanItem *childItem = parentItem->children.value(row);
    if( !childItem )
        return QModelIndex();

    return createIndex(row, column, childItem);
}

int BooleanModel::rowCount(const QModelIndex &parent) const
{
    if( parent.column() > 0 )
        return 0;

    BooleanItem *parentItem = itemFromIndex(parent);
    if( !parentItem )
        return 0;

    return parentItem->children.count();
}

int BooleanModel::columnCount(const QModelIndex &parent) const
{
    /*列保持2列，第一列是节点类型，第二列是节点值*/
    return 2;
}

/*
根据一个子节点，获取它的父节点的模型索引。
首先，通过模型索引，获取真实的节点对象。
第二，通过节点对象的parent，获取父节点对象
第三，通过父节点对象，获取祖父节点对象，通过祖父节点，确定父节点的行号（不能通过父节点本身，获取自身的行号，因为行号保存在自身的父节点上）
*/
QModelIndex BooleanModel::parent(const QModelIndex &child) const
{
    BooleanItem *item = itemFromIndex(child);
    if( !item )
        return QModelIndex();

    BooleanItem *parentItem = item->parent;
    if( !parentItem )
        return QModelIndex();

    BooleanItem *grandParentItem = parentItem->parent;
    if( !grandParentItem )
        return QModelIndex();

    int row = grandParentItem->children.indexOf(parentItem);
    return createIndex(row, 0, parentItem);
}

QVariant BooleanModel::data(const QModelIndex &index, int role) const
{
    if( role != Qt::DisplayRole )
        return QVariant();

    BooleanItem *item = itemFromIndex(index);
    if( !item )
        return QVariant();

    if( index.column() == 0 )
    {
        switch( item->type )
        {
        case BooleanItem::Root:
            return tr("Root");
        case BooleanItem::OrExpression:
            return tr("OR Expression");
        case BooleanItem::AndExpression:
            return tr("AND Expression");
        case BooleanItem::NotExpression:
            return tr("NOT Expression");
        case BooleanItem::Atom:
            return tr("Atom");
        case BooleanItem::Identifier:
            return tr("Identifier");
        case BooleanItem::Operator:
            return tr("Operator");
        case BooleanItem::Punctuator:
            return tr("Punctuator");
        default:
            return tr("Unknown");
        }
    }
    else if( index.column() == 1 )
    {
        return item->str;
    }

    return QVariant();
}

QVariant BooleanModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( orientation == Qt::Horizontal && role == Qt::DisplayRole )
    {
        if( section == 0 )
            return tr("Node");
        else if( section == 1 )
            return tr("Value");
    }

    return QVariant();
}


/*用于从parent模型索引中提取父项*/
BooleanItem *BooleanModel::itemFromIndex(const QModelIndex &index) const
{
    if( index.isValid() )
    {
        return static_cast<BooleanItem *>(index.internalPointer());
    }
    else
    {
        return rootItem;
    }
}
