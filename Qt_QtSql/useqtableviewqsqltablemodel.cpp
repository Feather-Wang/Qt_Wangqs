#include "useqtableviewqsqltablemodel.h"

#include <QSqlTableModel>
#include <QTableView>
#include <QHBoxLayout>
#include <QHeaderView>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>

#include <QtDebug>

#include <QPushButton>
#include <QSqlRelationalDelegate>

UseQTableViewQSqlTableModel::UseQTableViewQSqlTableModel(QWidget *parent)
    :QDialog(parent)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("UseQTableViewQSqlTableModel.db");
    if( !db.open() )
    {
        qDebug() << "db open error";
    }
    qDebug() << "UseQTableViewQSqlTableModel --> db = " << db;

    /*这里如果不事先创建好表，就导致表头无法正常显示*/
    QSqlQuery query;
    qDebug() << query.exec("create table user(name varchar(100) not null, age int not null, primary key(name));");
        /*
    qDebug() << query.exec("insert into user(name, age) values('wangqingsong', 28);");
    qDebug() << query.exec("insert into user(name, age) values('zhangpenglan', 27);");
    qDebug() << query.exec("insert into user(name, age) values('wangxinyu', 1);");
*/
    model = new QSqlTableModel(NULL, QSqlDatabase::database());
    model->setTable("user");

    model->setSort(User_Name, Qt::AscendingOrder);
    /*设置标题头，如何不设置这个，将以数据库表的表头名设置每一列的列名*/
    model->setHeaderData(User_Name, Qt::Horizontal, tr("Name"));
    model->setHeaderData(User_Age, Qt::Horizontal, tr("Age"));
    model->select();
    view = new QTableView(this);
    view->setModel(model);
        view->setItemDelegate(new QSqlRelationalDelegate(view));


    view->setSelectionMode(QAbstractItemView::SingleSelection);
    view->setSelectionBehavior(QAbstractItemView::SelectRows);
    //view->setColumnHidden(User_Name, true);
    view->resizeColumnsToContents();
    view->setEditTriggers(QAbstractItemView::NoEditTriggers);
    view->setShowGrid(false);

    QHeaderView *header = view->horizontalHeader();
    header->setStretchLastSection(true);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(view);

    QPushButton *update = new QPushButton(this);
    update->setText(tr("update"));
    layout->addWidget(update);
    connect(update, SIGNAL(clicked(bool)), this, SLOT(updateSql()));

    setLayout(layout);

    setWindowTitle(tr("UseQTableViewQSqlTableModel"));
}

void UseQTableViewQSqlTableModel::updateSql()
{
    model->setTable("user");
    model->setFilter("name = 'wangqingsong'");
    model->select();

    if( model->rowCount() == 1 )
    {
        QSqlRecord record = model->record(0);
        record.setValue("age", record.value("age").toInt()+2);

        model->setRecord(0, record);
        qDebug() << model->submitAll();
    }
    /*如果不讲Filter清空，QTableView在显示得时候也会用该Filter去筛选数据*/
    model->setFilter("");

/*
    QSqlQuery query;

    qDebug() << query.exec("select * from user where name='wangqingsong';");
    while( query.next() )
    {
        QString name = query.value(0).toString();
        int age = query.value(1).toInt();
        qDebug() << "name = " << name << ", age = " << age;
    }
    */
}
