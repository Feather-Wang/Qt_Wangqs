#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H

#include <QTableWidget>

class MyTableWidget : public QTableWidget
{
public:
    MyTableWidget();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dropEvent(QDropEvent *event);

private:
    void performDrag();
    QString toCsv(const QString &plainText);
    QString toHtml(const QString &plainText);

    QPoint startPos;
};

#endif // MYTABLEWIDGET_H
