#include "testshow.h"
#include <QtWidgets>
#include <QVBoxLayout>

#include <QDebug>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>

TestShow::TestShow(QWidget *parent) : QWidget(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("database.db");
    if( !db.open() )
    {
        qDebug() << "db open error" + db.lastError().text();
    }
    qDebug() << "init_database --> db = " << db;

    /*这里如果不事先创建好表，就导致表头无法正常显示*/
    QSqlQuery query;
    qDebug() << query.exec("create table stock(name varchar(100) not null, unit varchar(100) not null, count int not null, remark varchar(100), primary key(name));");


    model = new QSqlTableModel(NULL, QSqlDatabase::database());
    model->setTable("stock");
    model->setHeaderData(0, Qt::Horizontal, tr("name"));
    model->setHeaderData(1, Qt::Horizontal, tr("unit"));
    model->setHeaderData(2, Qt::Horizontal, tr("count"));
    model->setHeaderData(3, Qt::Horizontal, tr("remark"));
    model->select();

    view = new QTableView;
    /*设置QTableView使用得Model*/
    view->setModel(model);
    //resultView->verticalHeader()->hide();
    /*设置表格每一列得宽度*/
    view->setColumnWidth(0, 200);
    view->setColumnWidth(1, 50);
    view->setColumnWidth(2, 100);
    view->setColumnWidth(3, 200);
    /*设置：使表格填充到整个界面，当界面拉伸时，多出来得部分通过扩展最后一列来填充*/
    view->horizontalHeader()->setStretchLastSection(true);
    /*设置：当单击某个表格时，使其整行都被选中*/
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    /*取消编辑功能*/
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(view);

    setLayout(layout);

    setFixedWidth(1000);
}
