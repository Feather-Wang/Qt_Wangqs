#ifndef TESTSHOW_H
#define TESTSHOW_H

#include <QWidget>

#include <QTableView>
#include <QSqlTableModel>

class TestShow : public QWidget
{
    Q_OBJECT
public:
    explicit TestShow(QWidget *parent = 0);

signals:

public slots:

private:
    QTableView *view;
    QSqlTableModel *model;
};

#endif // TESTSHOW_H
