#ifndef CURRENCYMODEL_H
#define CURRENCYMODEL_H

#include <QAbstractTableModel>

class CurrencyModel : public QAbstractTableModel
{
public:
    CurrencyModel(QObject *parent = 0);

    /*设置要保存的数据资源*/
    void setCurrencyMap(const QMap<QString, double> &map);
    /*获取行数*/
    int rowCount(const QModelIndex &parent) const;
    /*获取列数*/
    int columnCount(const QModelIndex &parent) const;
    /*设置项的数据*/
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    /*获取模型索引为index的数据*/
    QVariant data(const QModelIndex &index, int role) const;
    /*设置*/
    Qt::ItemFlags flags(const QModelIndex &index) const;

    /*返回头部的数据，一般为行名或列名*/
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;

private:
    double getAmount(int row, int column) const;
    void setAmount(int row, int column, double amount);
    /*通过row和column，计算amounts中的索引值*/
    int offsetOf(int row, int column) const;

    QString currencyAt(int offset) const;

    /*保存货币对美元的汇率，通过对美元的汇率，可以计算出两个货币之间的汇率*/
    QMap<QString, double> currencyMap;
    /*缓存各个货币之间的汇率*/
    QVector<double> amounts;
};

#endif // CURRENCYMODEL_H
