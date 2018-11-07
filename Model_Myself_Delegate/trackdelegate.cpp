#include "trackdelegate.h"
#include <QTimeEdit>
#include <QtDebug>

TrackDelegate::TrackDelegate(int durationColumn, QObject *parent)
    : QStyledItemDelegate(parent)
{
    this->durationColumn = durationColumn;
}

void TrackDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "paint()";
    if (index.column() == durationColumn) {
        int secs = index.model()->data(index, Qt::DisplayRole).toInt();
        QString text = QString("%1:%2").arg(secs / 60, 2, 10, QChar('0')).arg(secs % 60, 2, 10, QChar('0'));
        QTextOption o(Qt::AlignRight | Qt::AlignVCenter);
        /*绘制文本*/
        painter->drawText(option.rect, text, o);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}


/*
创建一个编辑器：当用户初始化编辑的时候，视图会调用createEditor()创建一个编辑器，然后利用这个项的当前数据调用setEditorData()来初始化编辑器
这里只处理了第二列，也就是持续时间的编辑，其他的列的编辑，调用QItemDelegate类的createEditor去完成
当完成了对时间项的编辑后，会发送信号editingFinished()，然后出发自定义槽commitAndCloseEditor()
*/
QWidget *TrackDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug() << "createEditor()";
    if (index.column() == durationColumn) {
        QTimeEdit *timeEdit = new QTimeEdit(parent);
        timeEdit->setDisplayFormat("mm:ss");
        connect(timeEdit, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
        return timeEdit;
    } else {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

/*
自定义槽：当持续时间编辑完后，触发。
获取持续时间的QTimeEdit对象，然后发送两个信号：提交编辑后的QTimeEdit对象，关闭QTimeEdit对象
*/
void TrackDelegate::commitAndCloseEditor()
{
    qDebug() << "commitAndCloseEditor()";
    QTimeEdit *editor = qobject_cast<QTimeEdit *>(sender());
    /*发送commitData()信号，通知视图用被编辑的数据替换已经存在的数据*/
    emit commitData(editor);
    /*发送closeEditor()信号，通知视图已经不再需要这个编辑器了，这时模型将会把它删除*/
    emit closeEditor(editor);
}

/*
初始化编辑器
当视图中的某一项，进入编辑模式时，调用该函数
*/
void TrackDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug() << "setEditorData()";
    if (index.column() == durationColumn) {
        int secs = index.model()->data(index, Qt::DisplayRole).toInt();
        QTimeEdit *timeEdit = qobject_cast<QTimeEdit *>(editor);
        timeEdit->setTime(QTime(0, secs / 60, secs % 60));
        qDebug() << timeEdit->text();
    } else {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}

/*
保存数据，当编辑完成后，发送commitData()信号，触发该操作，将修改后的数据，保存到模型中
*/
void TrackDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug() << "setModelData()";
    if (index.column() == durationColumn) {
        QTimeEdit *timeEdit = qobject_cast<QTimeEdit *>(editor);
        qDebug() << "setModelData() --> " << timeEdit->text();
        QTime time = timeEdit->time();
        int secs = (time.minute() * 60) + time.second();
        model->setData(index, secs);
    } else {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}
