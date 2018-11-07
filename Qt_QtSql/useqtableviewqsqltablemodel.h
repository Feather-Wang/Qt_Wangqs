#ifndef USEQTABLEVIEWQSQLTABLEMODEL_H
#define USEQTABLEVIEWQSQLTABLEMODEL_H

#include <QDialog>

class QSqlTableModel;
class QTableView;

class UseQTableViewQSqlTableModel : public QDialog
{
    Q_OBJECT

public:
    UseQTableViewQSqlTableModel(QWidget *parent = 0);

    enum
    {
        User_Name = 0,
        User_Age = 1,
    };

private slots:
    void updateSql();

private:
    QSqlTableModel *model;
    QTableView *view;
};

#endif // USEQTABLEVIEWQSQLTABLEMODEL_H
