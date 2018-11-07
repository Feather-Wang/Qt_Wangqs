#include "currencymodel.h"


CurrencyModel::CurrencyModel(QObject *parent)
    :QAbstractTableModel(parent)
{
}

int CurrencyModel::rowCount(const QModelIndex &parent) const
{
    return currencyMap.count();
}

int CurrencyModel::columnCount(const QModelIndex &parent) const
{
    return currencyMap.count();
}

Qt::ItemFlags CurrencyModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = QAbstractItemModel::flags(index);
    if( index.row() != index.column() )
        flags |= Qt::ItemIsEditable;
    return flags;
}

bool CurrencyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug("setData()\n");
    if( !index.isValid() || index.row() == index.column() || role != Qt::EditRole )
        return false;
   qDebug("setData()1\n");
    setAmount(index.row(), index.column(), value.toDouble());
   qDebug("setData()2\n");
    /*通过行序号和列序号生成模型索引*/
    QModelIndex transIndex = createIndex(index.column(), index.row());
   qDebug("setData()3\n");
    /*发送信号，表示数据改变了*/
    emit dataChanged(index, index);
    emit dataChanged(transIndex, transIndex);
   qDebug("setData()4\n");
    return true;
}
/*
data():
返回一个项的任意角色的值，这个项被指定为QModelIndex。
*/
QVariant CurrencyModel::data(const QModelIndex &index, int role) const
{
    if( !index.isValid() )
        return QVariant();

    /*如果请求的数据是文本位置，则返回垂直居中、靠右的位置值*/
    if( role == Qt::TextAlignmentRole )
    {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    }
    /*如果是显示角色，则计算汇率，返回字符串*/
    else if( role == Qt::DisplayRole )
    {
        QString rowCurrency = currencyAt(index.row());
        QString columnCurrency = currencyAt(index.column());

        if( currencyMap.value(rowCurrency) == 0.0 )
            return "####";

        /*先从缓存中获取，如果还没有缓存，则计算，然后将结果保存到缓存中*/
        double amount = offsetOf(index.row(), index.column());
        if( 0.0 == amount )
            amount = currencyMap.value(columnCurrency) / currencyMap.value(rowCurrency);
        return QString("%1").arg(amount, 0, 'f', 4);
    }

    return QVariant();
}

/*如果是显示角色，则返回保存在currencyMap中的货币名称*/
QVariant CurrencyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if( role != Qt::DisplayRole )
        return QVariant();
    return currencyAt(section);
}

/*初始化保存的数据*/
void CurrencyModel::setCurrencyMap(const QMap<QString, double> &map)
{
    currencyMap = map;
    resetInternalData();
}

/*获取头部的货币名，因为行头和列头都一样，所以这里就直接获取了*/
QString CurrencyModel::currencyAt(int offset) const
{
    return (currencyMap.begin() + offset).key();
}

/*根据row和column，获取缓存在amounts中的各个货币之间的汇率*/
double CurrencyModel::getAmount(int row, int column) const
{
    int index = offsetOf(row, column);
    if( index < 0 )
        return 0.0;

    return amounts[index];
}

void CurrencyModel::setAmount(int row, int column, double amount)
{
    int index = offsetOf(row, column);
    if( index < 0 )
        return;

    if( 0.0 < amounts.at(index) )
        amounts[index] = amount;
    else
        amounts.append(amount);
}

int CurrencyModel::offsetOf(int row, int column) const
{
    if( row < column )
        qSwap(row, column);
    return (row * (row - 1) / 2) + column;
}
