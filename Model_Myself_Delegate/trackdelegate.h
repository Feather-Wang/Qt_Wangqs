#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H

#include <QtGui>
#include <QStyledItemDelegate>



/*
这里使用QItemDelegate作为基类，所以可以从默认的委托实现中获益。如果想从头开始做则可以使用QAbstractItemDelegate作为基类。
在Qt 4.4以后，增加了一个QStyledItemDelegate类，可以作为默认的委托，该类与QItemDelegate类不同，QStyledItemDelegate将依赖于当前风格以回执出它的项。
*/


class TrackDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    TrackDelegate(int durationColumn, QObject *parent = 0);

    /*用于绘制项*/
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private slots:
    void commitAndCloseEditor();

private:
    int durationColumn;
};


#endif // TRACKDELEGATE_H
