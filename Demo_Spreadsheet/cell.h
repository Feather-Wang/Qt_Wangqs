#ifndef CELL_H
#define CELL_H

#include <QTableWidgetItem>

class Cell : public QTableWidgetItem
{
public:
    Cell();

    QTableWidgetItem *clone() const;
    void setData(int role, const QVariant &value);
    QVariant data(int role) const;
    void setFormula(const QString &formula);
    QString formula() const;
    void setDirty();

private:
    QVariant value() const;
    QVariant evalExpression(const QString &str, int &pos) const;
    QVariant evalTerm( const QString &str, int &pos) const;
    QVariant evalFactor( const QString &str, int &pos) const;

    /*使用mutable修饰的变量，可以在const函数中修饰这些变量*/
    /*QVariant变量，可以表示任意类型，比如double，比如QString*/
    mutable QVariant cachedValue;
    mutable bool cacheIsDirty;
};

#endif // CELL_H
