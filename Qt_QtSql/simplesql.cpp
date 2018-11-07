#include "simplesql.h"
#include <QtDebug>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlDriver>
#include <QSqlTableModel>

SimpleSQL::SimpleSQL()
{

}

/*
创建数据库连接
*/
void SimpleSQL::use_QSqDatabase()
{
    /*创建单个数据库连接*/
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    /*添加多个数据库驱动程序*/
    //QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", "OTHER");

    db.setDatabaseName("database.db");
    if( !db.open() )
    {
        qDebug() << "db open error";
    }
    qDebug() << "use_QSqlQuery_exec()1 --> db = " << db;

    /*1、如果数据库连接，是单一连接，当想使用其中的一个数据库时，可以这样做*/
    QSqlDatabase oneDB = QSqlDatabase::database();
    QSqlQuery query;
    query.exec("select * from user;");

    /*2、如果数据库连接，是多个数据库连接，当想使用其中的一个数据库时，可以这样做*/
    /*
    QSqlDatabase sqliteDB = QSqlDatabase::database("QSQLITE");
    QSqlQuery sqliteQuery(sqliteDB);
    sqliteQuery.exec("select * from user;");
    */
}

/*
1、执行SQL插入语句（数据不来自变量，直接指定，当数据来自于变量或其它来源时，就需要将数据组合进SQL语句，这样的话，本函数中使用的exec()去执行SQL语句，就不行了，当然，也可以先将变量和查询语句通过QString组合在一起，再调用exec()。还有一种更方便的函数，就是prepare()调用，具体请看use_prepare_function()函数的演示）
2、执行查询语句，并遍历，打印查询结果
3、还有一些QSqlQuery的常规操作
*/
void SimpleSQL::use_QSqlQuery_exec()
{
    qDebug() << "use_QSqlQuery_exec().............";
    QSqlQuery query;

    /*使用QSqlQuery::exec()函数执行sql语句，返回值是布尔值，用于判断是否执行成功*/
    qDebug() << query.exec("create table user(name varchar(100) not null, age int not null, primary key(name));");

    qDebug() << query.exec("insert into user(name, age) values('wangqingsong', 28);");
    qDebug() << query.exec("insert into user(name, age) values('zhangpenglan', 27);");
    qDebug() << query.exec("insert into user(name, age) values('wangxinyu', 1);");

    /*
     * 当使用QSqlQuery::exec()执行查询语句时，查询结果将会保存在QSqlQuery对象中。
     * 通过next()函数，遍历每一条记录，访问第一条记录时，必须先调用一次next()，这是因为刚开始指向的是一个空记录，调用一次next()后，才是指向的第一条记录。之后，每调用一次next()，都指向下一条记录，当然，如果没有查询到任何信息，第一次调用next()时，将会返回false。
     * 指向记录后，通过value()函数，将数据取出来，value(0)就是去记录中的第一个数据，value(1)就是第二个，以此类推。因为value()返回的是QVariant，所以还需要使用toString()，toInt()等，转变成真正想要的类型的数据。
    */
    qDebug() << query.exec("select * from user");


    //该语句貌似是指定，遍历记录时，只能向最后一条记录的方向遍历，不能依靠first()，seek()等转向其他的记录，如果调用了first()，seek()等函数，将会报运行时错误。
    //query.setForwardOnly(true);
    while( query.next() )
    {
        QString name = query.value(0).toString();
        int age = query.value(1).toInt();
        qDebug() << "name = " << name << ", age = " << age;
    }

    /*指向第一条记录*/
    query.first();
    /*指向最后一条记录*/
    query.last();
    /*指向前一条记录*/
    query.previous();
    /*指向第一条记录（记录的序号是从0开始的）*/
    query.seek(2);
    /*获取现在指向的记录，不过返回值是一个QSqlRecord对象*/
    query.record();
    /*获取"name"属性的列号*/
    qDebug() << "the num of name is " << query.record().indexOf("name");
    /*返回每条记录中属性的个数*/
    qDebug() << "count of record is " << query.record().count();
    /*获取目前指向的记录的序号*/
    qDebug() << query.at();
    /*返回受SQL语句影响的行数，如果发生错误，就返回-1*/
    qDebug() << query.numRowsAffected();
    qDebug() << query.value(0).toString();
    /*在重复执行SQL语句之前调用，通知数据库驱动程序，没有数据需要拿了，一般情况下是不需要调用finish()的，但是在某些情况下，还是有用的，比如释放保存查询到的数据的资源。同时，该函数将会让QSqlQuery退出激活状态*/
    query.finish();
    /*判断QSqlQuery是否处于激活状态，当QSqlQuery成功执行一条SQL语句后，就会进入激活状态*/
    if( query.isActive() )
    {
        qDebug() << "query.exec is error";
    }
}

/*
如果需要插入多条记录，或者想避免将数值转换成为字符串（并且正确的转义它们），可以使用prepare()来指定一个包含占位符的查询，然后赋值绑定想插入的数值。
Qt对所有数据库都支持Oracle风格和ODBC风格的占位符语法，如果它们可用，就使用本地支持，如果不可用，就模拟它的功能。
在Qt中，首先，通过QSqlQuery::prepare()设定好SQL语句，并设置好占位符。
然后，通过QSqlQuery::bindValue()或者QSqlQuery::addBindValue()来赋值绑定新值。
最后调用QSqlQuery::exec()执行SQL语句。
如果设置的SQL语句相同，并且占位符相同，那么prepare()可以只调用一次，接下来只需要循环调用QSqlQuery::bindValue()(或者addBindValue)和exec()就可以了。
占位符通常用于指定二进制数据或者包含非ASCII码或者非Latin字符的字符串。
在底层，Qt对支持Unicode的数据库使用Unicode编码，而对于不支持Unicode的，Qt会明确地把字符串转换为合适的编码方式。
*/
void SimpleSQL::use_QSqlQuery_prepare_exec()
{
    qDebug() << "use_QSqlQuery_prepare_exec().............";

    /*因为已经在use_QSqlQuery()连接上数据库了，所以这里就不重复连接了*/

    QSqlQuery query;
    /*第一，演示Oracle风格语法及命名占位符*/
    query.prepare("insert into user(name, age) values(:name, :age);");

    query.bindValue(":name", "nihao");
    query.bindValue(":age", 100);
    qDebug() << "query.exec() first " << query.exec();

    query.bindValue(":name", "helloworld");
    query.bindValue(":age", 101);
    qDebug() << "query.exec() second " << query.exec();

    /*第二，演示ODBC风格语法及命名占位符*/
    query.prepare("insert into user(name, age) values(?, ?);");

    query.addBindValue("bindname");
    query.addBindValue("105");
    qDebug() << "query.exec() third " << query.exec();

    query.addBindValue("bindname2");
    query.addBindValue("106");
    qDebug() << "query.exec() fourth " << query.exec();
}

/*
事务操作，以及对数据库驱动程序，是否支持事务操作进行检查
*/
void SimpleSQL::use_QSqlDatabase_transaction()
{
    qDebug() << "use_QSqlDatabase_transaction().............";

    /*因为已经在use_QSqlQuery()连接上数据库了，所以这里就不重复连接了*/

    /*开启事务，在这里调用database()返回一个表示在use_QSqlQuery()中创建的连接QSqlDatabase对象，因为这里只创建了QSQLITE数据库，所以在调用database()时不需要指定参数，如果是添加了多少数据库驱动，则需要指定驱动程序名，例如：QSqlDatabase::database("QSQLITE")*/
    /*如果事务不能启动，则返回false。对于一些数据库不支持事务操作，对于这类数据库，transaction()、commit()和rollback()就什么都不做，可以通过hasFeature()对数据库相关的QSqlDriver进行测试，看看这个数据库是否支持事务操作*/
    QSqlDriver *driver = QSqlDatabase::database().driver();
    if( driver->hasFeature(QSqlDriver::Transactions) )
    {
        qDebug() << "表示支持事务操作";
    }

    QSqlDatabase::database().transaction();

    QSqlQuery query;
    qDebug() << "use_transaction() 1 --> " << query.exec("insert into user(name, age) values('transaction_01', 201);");

    /*结束事务，也可以调用rollback()结束事务*/
    QSqlDatabase::database().commit();
    qDebug() << QSqlDatabase::database().databaseName();
}

/*
Qt提供了QSqlTableModel类作为一个高级界面接口，让我们不必使用原始的SQL语句来执行大多数常用的SQL操作。
这个类可以用来独立处理数据库而不涉及任何的图形用户界面，它也可以用作QListView或QTableView的模型，提供数据。
SQL模型与标准模型之间最大的区别在于：对于SQL模型，必须调用submitAll()以将发生的更改写入数据库。

除了QSqlTableModel类外，Qt还提供了其它的模型类
1、QSqlQueryModel：是QSqlTableModel的父类
2、QSqlRelationalTableModel：是QSqlTableModel的子类，可以利用外键来显示好编辑表，除了可以为每一个外键将QSqlTableModel添加到模型，其它的都跟QSqlTableModel非常相似。
*/
void SimpleSQL::use_QSqlTableModel()
{
    qDebug() << "use_QSqlTableModel().............";

    QSqlTableModel model(NULL, QSqlDatabase::database());
    model.setTable("user");
    //model.setFilter("age >= 100");
    model.select();

    for( int i = 0; i < model.rowCount(); ++i )
    {
        QSqlRecord record = model.record(i);
        QString name = record.value("name").toString();
        int age = record.value("age").toInt();
        qDebug() << "QSqlTableModel() --> select : name = " << name << ", age = " << age;
    }

    /*
    关于使用QSqlTableModel插入数据。
    首先使用insertRows在row行，插入n个空行（由第二个参数指定）。
    然后，通过setData()指定数据。
    最后使用submitAll()提交数据
    */
    model.setTable("user");
    int row = 0;
    model.insertRows(row, 1);
    model.setData(model.index(row, 0), "model_01");
    model.setData(model.index(row, 1), 701);
    /*提交所有数据，记录可能会被移动到一个不同的行位置，这取决于表是如何排序的，如果插入失败，submitAll()会返回false*/
    model.submitAll();

    /*
    关于使用QSqlTableModel更新记录。
    首先，必须把记录提取出来，比如使用select()。
    然后，修改提取出来的记录，有两种修改方式：
        1、通过QSqlTableModel::record()获取记录，然后在QSqlRecord对象中修改，然后通过QSqlTableModel::setRecord()将修改后的QSqlRecord写入model
        2、直接通过QSqlTableModel::setData()，通过要修改的项的索引，进行修改
    最后，调用submitAll()提交记录。
    */
    model.setTable("user");
    model.setFilter("name = 'model_01'");
    model.select();
    if( model.rowCount() == 1 )
    {
        QSqlRecord record = model.record(0);
        record.setValue("age", record.value("age").toInt()+2);

        model.setRecord(0, record);
        model.submitAll();
    }
    model.setTable("user");
    model.setFilter("name = 'model_01'");
    model.select();
    if( model.rowCount() == 1 )
    {
        model.setData(model.index(0, 1), 1002);
        model.submitAll();
    }

    /*
    删除记录。
    首先，通过select()获取要删除的记录。
    然后，使用removeRow()或者removeRows()删除记录。
    最后，使用submitAll()提交操作。
    */
    model.setTable("user");
    model.setFilter("name = 'model_01'");
    model.select();
    if( model.rowCount() == 1 )
    {
        /*调用removeRow()或者removeRows()删除记录，removeRows比removeRow多一个参数，第二个参数是指定删除的记录的个数（以第一个参数指定的行数开始）*/
        //model.removeRow(0);
        model.removeRows(0, 1);

        model.submitAll();
    }
}
