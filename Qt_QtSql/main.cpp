#include <QApplication>

/*主要演示了一般的数据库操作流程*/
#include "simplesql.h"
/*QTableView和QSqlTableModel结合*/
#include "useqtableviewqsqltablemodel.h"
/*使用QSqlRelationalTableModel和QTableView，设置了两个QTableView，互为主从，通过点击主表的记录，在从表中显示不同的数据*/
#include "mainform.h"

/*
使用QtSql接口，需要在pro文件中添加QT += sql。这将确保应用程序可以连接到QtSql库。
*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*该代码片段，演示了数据库操作得各种方式，包括使用数据库类，已经QSqlTableModel模型*/
/*
    SimpleSQL sql;
    sql.use_QSqDatabase();
    sql.use_QSqlQuery_exec();
    sql.use_QSqlQuery_prepare_exec();
    sql.use_QSqlDatabase_transaction();
    sql.use_QSqlTableModel();
*/

    UseQTableViewQSqlTableModel tableView;
    tableView.show();
/*
    MainForm table;
    table.show();
*/
    return a.exec();
}
