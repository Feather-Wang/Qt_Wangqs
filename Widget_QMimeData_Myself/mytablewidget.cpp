#include "mytablewidget.h"

#include <QtGui>
#include <QApplication>
#include "tablemimedata.h"

MyTableWidget::MyTableWidget()
{

}

void MyTableWidget::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
        startPos = event->pos();
}

/*
 * 计算抖动值，获取从原点到当前点之间的距离
 * manhattanLength()是曼哈顿长度，即从坐标原点到该矢量长度快速计算的近似值。
 * 当曼哈顿长度大于或等于QApplication推荐的拖动起始距离值（通常是4个像素），
 * 那么就调用performDrag()以启动拖动操作，
 * 这样可以避免用户因为手握鼠标抖动而产生拖动。
*/
void MyTableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if( event->buttons() & Qt::LeftButton )
    {
        int distance = (event->pos() - startPos).manhattanLength();
        if( distance >= QApplication::startDragDistance() )
            performDrag();
    }

    QTableWidget::mouseMoveEvent(event);
}

void MyTableWidget::performDrag()
{
    QString plainText = "wang qing song";
    if( plainText.isEmpty() )
        return;

    QMimeData *mimeData = new QMimeData;
    mimeData->setText(plainText);
    mimeData->setHtml(toHtml(plainText));
    mimeData->setData("text/csv", toCsv(plainText).toUtf8());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    if( drag->exec(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction )
        return;
}

QString MyTableWidget::toCsv(const QString &plainText)
{
    QString result = plainText;
    result.replace("\\", "\\\\");
    result.replace("\"", "\\\"");
    result.replace("\t", "\", \"");
    result.replace("\n", "\"\n\"");
    result.prepend("\"");
    result.append("\"");

    return result;
}

QString MyTableWidget::toHtml(const QString &plainText)
{
    QString result = plainText;
    result.replace("\t", "<td>");
    result.replace("\n", "\n<tr><td>");
    result.prepend("<table>\n<tr><td>");
    result.append("\n</table>");

    return result;
}

void MyTableWidget::dropEvent(QDropEvent *event)
{
    const TableMimeData *tableData = qobject_cast<const TableMimeData *>(event->mimeData());

    if( tableData )
    {
        const QTableWidget *otherTable = tableData->tableWidget();
        QTableWidgetSelectionRange otherRange = tableData->range();
        event->acceptProposedAction();
    }
    else if( event->mimeData()->hasFormat("text/csv") )
    {
        QByteArray csvData = event->mimeData()->data("text/csv");
        QString csvText = QString::fromUtf8(csvData);

        event->acceptProposedAction();
    }
    else if( event->mimeData()->hasFormat("text/plain") )
    {
        QString plainText = event->mimeData()->text();
        event->acceptProposedAction();
    }
}
