#ifndef SIMPLESQL_H
#define SIMPLESQL_H


class SimpleSQL
{
public:
    SimpleSQL();

    /*以下函数，是创建的数据库连接*/
    void use_QSqDatabase();
    /*以下四个函数，都是使用的单一的数据库连接*/
    void use_QSqlQuery_exec();
    void use_QSqlQuery_prepare_exec();
    void use_QSqlDatabase_transaction();
    void check_driver();

    /*使用数据库模型QSqlTableModel*/
    void use_QSqlTableModel();
};

#endif // SIMPLESQL_H
