#include "wqs_erp.h"
#include "stock_change_dialog.h"
#include "wordengine.h"

#include <Qdate>


wqs_erp::wqs_erp(QWidget *parent) : QWidget(parent)
{
    init_database();
    init_model();
    init_view();
    init_layout();
}

void wqs_erp::init_database()
{
    qDebug() << "init_database()";

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("wqs_erp.db");
    if( !db.open() )
    {
        qDebug() << "db open error" + db.lastError().text();
    }
    qDebug() << "init_database --> db = " << db;

    /*这里如果不事先创建好表，就导致表头无法正常显示*/
    QSqlQuery query;
    qDebug() << query.exec("create table stock(name varchar(100) not null, unit varchar(100) not null, count int not null, remark varchar(100), primary key(name));");
    qDebug() << query.exec("create table stock_history(name varchar(100) not null, unit varchar(100) not null, count int not null, price double not null, operation varchar(100) not null, operation_time varchar(100) not null, partner varchar(100) not null, remark varchar(100));");
}

void wqs_erp::init_model()
{
    qDebug() << "init_model()";

    data_model_stock = new QSqlTableModel(NULL, QSqlDatabase::database());
    data_model_stock->setTable("stock");
    data_model_stock->setHeaderData(0, Qt::Horizontal, stock_name_china.at(Index_stock_name));
    data_model_stock->setHeaderData(1, Qt::Horizontal, stock_name_china.at(Index_stock_unit));
    data_model_stock->setHeaderData(2, Qt::Horizontal, stock_name_china.at(Index_stock_count));
    data_model_stock->setHeaderData(3, Qt::Horizontal, stock_name_china.at(Index_stock_remark));
    data_model_stock->select();

    data_model_stock_history = new QSqlTableModel(NULL, QSqlDatabase::database());
    data_model_stock_history->setTable("stock_history");
    data_model_stock_history->setHeaderData(0, Qt::Horizontal, stock_history_name_china.at(Index_stock_history_name));
    data_model_stock_history->setHeaderData(1, Qt::Horizontal, stock_history_name_china.at(Index_stock_history_unit));
    data_model_stock_history->setHeaderData(2, Qt::Horizontal, stock_history_name_china.at(Index_stock_history_count));
    data_model_stock_history->setHeaderData(3, Qt::Horizontal, stock_history_name_china.at(Index_stock_history_price));
    data_model_stock_history->setHeaderData(4, Qt::Horizontal, stock_history_name_china.at(Index_stock_history_operation));
    data_model_stock_history->setHeaderData(5, Qt::Horizontal, stock_history_name_china.at(Index_stock_history_operation_time));
    data_model_stock_history->setHeaderData(6, Qt::Horizontal, stock_history_name_china.at(Index_stock_history_partner));
    data_model_stock_history->setHeaderData(7, Qt::Horizontal, stock_history_name_china.at(Index_stock_history_remark));
    data_model_stock_history->select();
}

void wqs_erp::init_view()
{
    qDebug() << "init_view()";
    /*1、。。。。。。。。。。。。。。。QTableView*/
    data_view_stock = new QTableView;
    /*设置QTableView使用得Model*/
    data_view_stock->setModel(data_model_stock);
    //resultView->verticalHeader()->hide();
    /*设置QTableView得双击信号-槽，通过双击操作实现对指定记录得入库、出库操作*/
    connect(data_view_stock, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_action_oparetion()));
    /*设置表格每一列得宽度*/
    data_view_stock->setColumnWidth(0, 200);
    data_view_stock->setColumnWidth(1, 50);
    data_view_stock->setColumnWidth(2, 100);
    data_view_stock->setColumnWidth(3, 200);
    /*设置：使表格填充到整个界面，当界面拉伸时，多出来得部分通过扩展最后一列来填充*/
    data_view_stock->horizontalHeader()->setStretchLastSection(true);
    /*设置：当单击某个表格时，使其整行都被选中*/
    data_view_stock->setSelectionBehavior(QAbstractItemView::SelectRows);
    /*取消编辑功能*/
    data_view_stock->setEditTriggers(QAbstractItemView::NoEditTriggers);

    data_view_stock_history = new QTableView;
    /*设置QTableView使用得Model*/
    data_view_stock_history->setModel(data_model_stock_history);
    /*设置表格每一列得宽度*/
    data_view_stock_history->setColumnWidth(0, 200);
    data_view_stock_history->setColumnWidth(1, 50);
    data_view_stock_history->setColumnWidth(2, 100);
    data_view_stock_history->setColumnWidth(3, 100);
    data_view_stock_history->setColumnWidth(4, 100);
    data_view_stock_history->setColumnWidth(5, 150);
    data_view_stock_history->setColumnWidth(6, 50);
    data_view_stock_history->setColumnWidth(7, 200);
    /*设置：使表格填充到整个界面，当界面拉伸时，多出来得部分通过扩展最后一列来填充*/
    data_view_stock_history->horizontalHeader()->setStretchLastSection(true);
    /*设置：当单击某个表格时，使其整行都被选中*/
    data_view_stock_history->setSelectionBehavior(QAbstractItemView::SelectRows);
    /*取消编辑功能*/
    data_view_stock_history->setEditTriggers(QAbstractItemView::NoEditTriggers);
    data_view_stock_history->hide();

    /*2、。。。。。。。。。。。。。查询历史操作记录时使用得开始时间和结束时间*/
    QDate date_start = QDate::currentDate();
    time_end = new QDateEdit;
    time_end->setCalendarPopup(true);
    time_end->setDate(date_start);
    time_end->hide();

    time_start = new QDateEdit;
    time_start->setCalendarPopup(true);
    time_start->setDate(date_start.addMonths(-3));
    time_start->hide();

    /*3、。。。。。。。。。。。。。各个功能下得动作控件*/
    action_oparetion_type = Action_Push;

    search_stock_name = new QComboBox;
    for(int i = 0; i < stock_name_china.count(); i++)
    {
        search_stock_name->addItem(stock_name_china.at(i));
    }
    search_stock_name->setFixedWidth(150);
    search_text = new QLineEdit;
    search_text->setFixedWidth(150);

    action_search = new QPushButton;
    action_search->setText(tr("过滤查询"));
    //action_search->setHidden(true);
    connect(action_search, SIGNAL(clicked(bool)), this, SLOT(slot_action_search()));
    action_statistics_word = new QPushButton;
    action_statistics_word->setText(tr("生成操作清单"));
    action_statistics_word->hide();
    connect(action_statistics_word, SIGNAL(clicked(bool)), this, SLOT(slot_action_statistics_word()));

    action_push = new QPushButton;
    action_push->setText(tr("新增产品信息"));
    connect(action_push, SIGNAL(clicked(bool)), this, SLOT(slot_action_oparetion()));

    label_history_push_total = new QLabel;
    label_history_push_total->setText(tr("入库金额"));
    label_history_push_total->setFixedWidth(100);
    label_history_push_total->hide();
    label_history_pop_total = new QLabel;
    label_history_pop_total->setText(tr("出库金额"));
    label_history_pop_total->setFixedWidth(100);
    label_history_pop_total->hide();

    lineedit_history_push_total = new QLineEdit;
    lineedit_history_push_total->setDisabled(false);
    lineedit_history_push_total->setFixedWidth(100);
    lineedit_history_push_total->hide();
    lineedit_history_pop_total = new QLineEdit;
    lineedit_history_pop_total->setDisabled(false);
    lineedit_history_pop_total->setFixedWidth(100);
    lineedit_history_pop_total->hide();

    /*4、。。。。。。。。功能按钮设置*/
    function_push = new QPushButton;
    function_push->setText(tr("入库操作"));
    /*默认使用得是入库操作，所以把该按钮得背景颜色初始化为功能选中色*/
    function_push->setStyleSheet("background:red");
    function_pop = new QPushButton;
    function_pop->setText(tr("出库操作"));
    function_history = new QPushButton;
    function_history->setText(tr("历史单据查询"));
    /*设置功能按钮得信号-槽，只要是处理部分控件得隐藏-显示，以及功能按钮得背景色显示*/
    connect(function_push, SIGNAL(clicked(bool)), this, SLOT(slot_action_button()));
    connect(function_pop, SIGNAL(clicked(bool)), this, SLOT(slot_action_button()));
    connect(function_history, SIGNAL(clicked(bool)), this, SLOT(slot_action_button()));
}

void wqs_erp::init_layout()
{
    qDebug() << "init_layout()";

    QHBoxLayout *layout_function = new QHBoxLayout;
    layout_function->addWidget(function_push);
    layout_function->addWidget(function_pop);
    layout_function->addWidget(function_history);

    QHBoxLayout *layout_action = new QHBoxLayout;
    layout_action->addWidget(time_start);
    layout_action->addWidget(time_end);

    layout_action->addWidget(search_stock_name);
    layout_action->addWidget(search_text);

    layout_action->addWidget(action_search);
    layout_action->addWidget(action_push);
    layout_action->addWidget(action_statistics_word);

    QHBoxLayout *layout_history_total = new QHBoxLayout;
    layout_history_total->addWidget(label_history_push_total);
    layout_history_total->addWidget(lineedit_history_push_total);
    layout_history_total->addWidget(label_history_pop_total);
    layout_history_total->addWidget(lineedit_history_pop_total);
    layout_history_total->addStretch(1);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout_function);
    layout->addLayout(layout_action);
    layout->addLayout(layout_history_total);
    layout->addWidget(data_view_stock);
    layout->addWidget(data_view_stock_history);
    setLayout(layout);
    setFixedWidth(1000);
    //setFixedHeight(300);
}

void wqs_erp::slot_action_oparetion()
{
    int temp_count = 0;
    int action_type = 0;

    if( action_oparetion_type == Action_Push )
        action_type = stock_change_dialog::Action_Type_Push;
    else if( action_oparetion_type == Action_Pop )
        action_type = stock_change_dialog::Action_Type_Pop;

    stock_change_dialog dialog(action_type, this);
    if( action_oparetion_type == Action_Push )
        dialog.setWindowTitle(tr("新增库存"));
    else
        dialog.setWindowTitle(tr("去库存"));


    QObject *action = qobject_cast<QObject *>(sender());
    qDebug() << "---" << (action == data_view_stock);
    if( action == data_view_stock )
    {
        qDebug() << "slot_action_push() --> 选中行为："
                 << data_model_stock->index(data_view_stock->currentIndex().row(), 0).data().toString()
                 << ":"
                 << data_model_stock->index(data_view_stock->currentIndex().row(), 1).data().toString()
                 << ":"
                 << data_model_stock->index(data_view_stock->currentIndex().row(), 2).data().toInt()
                 << ":"
                 << data_model_stock->index(data_view_stock->currentIndex().row(), 3).data().toString();

        dialog.setName(data_model_stock->index(data_view_stock->currentIndex().row(), 0).data().toString());
        dialog.setUnit(data_model_stock->index(data_view_stock->currentIndex().row(), 1).data().toString());
        temp_count = data_model_stock->index(data_view_stock->currentIndex().row(), 2).data().toInt();
    }
    else
    {
        dialog.setHideLabel(stock_change_dialog::Index_Price);
        dialog.setHideLabel(stock_change_dialog::Index_Count);
        dialog.setHideLabel(stock_change_dialog::Index_Partner);
    }

    bool result = dialog.exec();
    qDebug() << "dialog.exec()" << result;
    if( result )
    {
        qDebug() << "dialog.exec()" << result << ":" << dialog.getName()
                 << ":"
                 << dialog.getUnit()
                 << ":"
                 << dialog.getPrice()
                 << ":"
                 << dialog.getCount()
                 << ":"
                 << dialog.getRemark();

        if( action == data_view_stock )
        {
            data_model_stock->setFilter("name = '"+dialog.getName()+"'");
            qDebug() << "slot_action_push --> Filter=" << data_model_stock->filter();
            data_model_stock->select();

            if( data_model_stock->rowCount() == 1 )
            {
                QSqlRecord record = data_model_stock->record(0);
                if( action_oparetion_type == Action_Push )
                    record.setValue("count", dialog.getCount() + temp_count);
                else
                    record.setValue("count", temp_count - dialog.getCount());

                data_model_stock->setRecord(0, record);
                qDebug() << data_model_stock->submitAll();
            }
            /*如果不讲Filter清空，QTableView在显示得时候也会用该Filter去筛选数据*/
            data_model_stock->setFilter("");
        }
        else
        {
            data_model_stock->insertRows(0, 1);
            data_model_stock->setData(data_model_stock->index(0, 0), dialog.getName());
            data_model_stock->setData(data_model_stock->index(0, 1), dialog.getUnit());
            data_model_stock->setData(data_model_stock->index(0, 2), 0);
            data_model_stock->setData(data_model_stock->index(0, 3), dialog.getRemark());
            data_model_stock->submitAll();
            return;
        }

        if( action_oparetion_type == Action_Push )
        {
            qDebug() << "action_oparetion_type == Action_Push 1->" << data_model_stock_history->insertRows(0, 1);
            qDebug() << "action_oparetion_type == Action_Push 2->" << data_model_stock_history->setData(data_model_stock_history->index(0, 0), dialog.getName());
            qDebug() << "action_oparetion_type == Action_Push 3->" << data_model_stock_history->setData(data_model_stock_history->index(0, 1), dialog.getUnit());
            qDebug() << "action_oparetion_type == Action_Push 4->" << data_model_stock_history->setData(data_model_stock_history->index(0, 2), dialog.getCount());
            qDebug() << "action_oparetion_type == Action_Push 5->" << data_model_stock_history->setData(data_model_stock_history->index(0, 3), dialog.getPrice());
            qDebug() << "action_oparetion_type == Action_Push 6->" << data_model_stock_history->setData(data_model_stock_history->index(0, 4), tr("入库"));
            qDebug() << "action_oparetion_type == Action_Push 7->" << data_model_stock_history->setData(data_model_stock_history->index(0, 5), QDateTime::currentDateTime().toString(tr("yyyy/MM/dd hh:mm"))) << QDateTime::currentDateTime().toString(tr("yyyy/MM/dd hh:mm"));
            qDebug() << "action_oparetion_type == Action_Push 7->" << data_model_stock_history->setData(data_model_stock_history->index(0, 6), dialog.getPartner());
            qDebug() << "action_oparetion_type == Action_Push 8->" << data_model_stock_history->setData(data_model_stock_history->index(0, 7), dialog.getRemark());
            qDebug() << "action_oparetion_type == Action_Push 9->" << data_model_stock_history->submitAll();
            qDebug() << "action_oparetion_type == Action_Push 10->" << data_model_stock_history->lastError();
        }
        else
        {
            data_model_stock_history->insertRows(0, 1);
            data_model_stock_history->setData(data_model_stock_history->index(0, 0), dialog.getName());
            data_model_stock_history->setData(data_model_stock_history->index(0, 1), dialog.getUnit());
            data_model_stock_history->setData(data_model_stock_history->index(0, 2), dialog.getCount());
            data_model_stock_history->setData(data_model_stock_history->index(0, 3), dialog.getPrice());
            data_model_stock_history->setData(data_model_stock_history->index(0, 4), tr("出库"));
            data_model_stock_history->setData(data_model_stock_history->index(0, 5), QDateTime::currentDateTime().toString(tr("yyyy/MM/dd hh:mm")));
            data_model_stock_history->setData(data_model_stock_history->index(0, 6), dialog.getPartner());
            data_model_stock_history->setData(data_model_stock_history->index(0, 7), dialog.getRemark());
            data_model_stock_history->submitAll();
        }
    }
}

void wqs_erp::slot_action_search()
{
    qDebug() << "slot_action_search() --> [" << search_text->text().simplified() << "]" << search_text->text().simplified().isEmpty();
    int index = 0;
    if( action_oparetion_type == Action_Push || action_oparetion_type == Action_Pop )
    {
        if( search_text->text().simplified().isEmpty() )
            data_model_stock->setFilter(tr(""));
        else
        {
            index = search_stock_name->currentIndex();
            if( index == Index_stock_name || index == Index_stock_unit || index == Index_stock_remark )
                data_model_stock->setFilter(stock_name.at(index) + "= '" + search_text->text() + "'");
            else
                data_model_stock->setFilter(stock_name.at(index) + "= " + search_text->text());
        }
    }
    else
    {
        if( search_text->text().simplified().isEmpty() )
            data_model_stock_history->setFilter(stock_history_name.at(Index_stock_history_operation_time) + " >= '" + time_start->date().toString(tr("yyyy/MM/dd")) + "' and " + stock_history_name.at(Index_stock_history_operation_time) + " <= '" + time_end->date().addDays(1).toString(tr("yyyy/MM/dd")) + "'");
        else
        {
            index = search_stock_name->currentIndex();
            if( index == Index_stock_history_name ||
                    index == Index_stock_history_unit ||
                    index == Index_stock_history_operation ||
                    index == Index_stock_history_partner ||
                    index == Index_stock_history_remark )
                data_model_stock_history->setFilter(stock_history_name.at(Index_stock_history_operation_time) + " >= '" + time_start->date().toString(tr("yyyy/MM/dd")) + "' and " + stock_history_name.at(Index_stock_history_operation_time) + " <= '" + time_end->date().addDays(1).toString(tr("yyyy/MM/dd")) + "' and " + stock_history_name.at(index) + "= '" + search_text->text() + "'");
            else
                data_model_stock_history->setFilter(stock_history_name.at(Index_stock_history_operation_time) + " >= '" + time_start->date().toString(tr("yyyy/MM/dd")) + "' and " + stock_history_name.at(Index_stock_history_operation_time) + " <= '" + time_end->date().addDays(1).toString(tr("yyyy/MM/dd")) + "' and " + stock_history_name.at(index) + "= " + search_text->text());
        }

        statistics_total();
    }
}

void wqs_erp::slot_action_button()
{
    QObject *action = qobject_cast<QObject *>(sender());
    qDebug() << "slot_action_button--->" << (action == data_model_stock);
    if( action == function_push )
    {
        time_start->hide();
        time_end->hide();
        action_push->show();
        action_statistics_word->hide();
        data_view_stock->show();
        data_view_stock_history->hide();

        label_history_push_total->hide();
        label_history_pop_total->hide();
        lineedit_history_push_total->hide();
        lineedit_history_pop_total->hide();

        function_push->setStyleSheet("background:red");
        function_pop->setStyleSheet("");
        function_history->setStyleSheet("");

        action_oparetion_type = Action_Push;

        search_stock_name->clear();
        for(int i = 0; i < stock_name_china.count(); i++)
        {
            search_stock_name->addItem(stock_name_china.at(i));
        }
        search_text->clear();
        data_model_stock->setFilter(tr(""));
    }
    else if( action == function_pop )
    {
        time_start->hide();
        time_end->hide();
        action_push->hide();
        action_statistics_word->hide();
        data_view_stock->show();
        data_view_stock_history->hide();

        label_history_push_total->hide();
        label_history_pop_total->hide();
        lineedit_history_push_total->hide();
        lineedit_history_pop_total->hide();

        function_push->setStyleSheet("");
        function_pop->setStyleSheet("background:red");
        function_history->setStyleSheet("");

        action_oparetion_type = Action_Pop;

        search_stock_name->clear();
        for(int i = 0; i < stock_name_china.count(); i++)
        {
            search_stock_name->addItem(stock_name_china.at(i));
        }
        search_text->clear();
        data_model_stock->setFilter(tr(""));
    }
    else if( action == function_history )
    {
        time_start->show();
        time_end->show();
        action_push->hide();
        action_statistics_word->show();
        data_view_stock->hide();
        data_view_stock_history->show();

        label_history_push_total->show();
        label_history_pop_total->show();
        lineedit_history_push_total->show();
        lineedit_history_pop_total->show();

        function_push->setStyleSheet("");
        function_pop->setStyleSheet("");
        function_history->setStyleSheet("background:red");

        action_oparetion_type = Action_Null;

        search_stock_name->clear();
        for(int i = 0; i < stock_history_name_china.count(); i++)
        {
            search_stock_name->addItem(stock_history_name_china.at(i));
        }
        search_text->clear();
        data_model_stock_history->setFilter(stock_history_name.at(Index_stock_history_operation_time) + " >= '" + time_start->date().toString(tr("yyyy/MM/dd")) + "' and " + stock_history_name.at(Index_stock_history_operation_time) + " <= '" + time_end->date().addDays(1).toString(tr("yyyy/MM/dd")) + "'");
        statistics_total();
    }
}

void wqs_erp::slot_action_statistics_word()
{
    statistics_word();
}

void wqs_erp::statistics_total()
{
    double total_push = 0;
    double total_pop = 0;

    data_model_stock_history->select();

    for( int i = 0; i < data_model_stock_history->rowCount(); ++i )
    {
        QSqlRecord record = data_model_stock_history->record(i);
        QString operation = record.value(stock_history_name.at(Index_stock_history_operation)).toString();
        if( operation == tr("入库") )
        {
            total_push += record.value(stock_history_name.at(Index_stock_history_count)).toInt() * record.value(stock_history_name.at(Index_stock_history_price)).toDouble();
        }
        else
        {
            total_pop += record.value(stock_history_name.at(Index_stock_history_count)).toInt() * record.value(stock_history_name.at(Index_stock_history_price)).toDouble();

        }
    }

    lineedit_history_push_total->setText(QString::number(total_push, 10, 2));
    lineedit_history_pop_total->setText(QString::number(total_pop, 10, 2));
    qDebug() << "statistics_total() --> " << total_push << total_pop;
}

void wqs_erp::statistics_word()
{
    data_model_stock_history->select();

    WordEngine engine;
    engine.Open(tr("d:/template.doc"), true);

    QStringList list;
    list << stock_history_name_china.at(Index_stock_history_name)
         << stock_history_name_china.at(Index_stock_history_unit)
         << stock_history_name_china.at(Index_stock_history_operation)
         << stock_history_name_china.at(Index_stock_history_count)
         << stock_history_name_china.at(Index_stock_history_price);
    qDebug() << "list = " << list;

    QAxObject *table = NULL;
    /*在标签wangqs_tables处，创建一个三行四列得表格，如果list非空，则表格头为list，如果为空，则表格无表头*/
    if( list.empty() )
        table = engine.insertTable("wangqs_tables", data_model_stock_history->rowCount(), 5);
    else
        table = engine.insertTable("wangqs_tables", data_model_stock_history->rowCount()+1, 5, list);

    for( int i = 0; i < data_model_stock_history->rowCount(); ++i )
    {
        QSqlRecord record = data_model_stock_history->record(i);

        engine.SetTableCellString(table, i+2, 1, record.value(stock_history_name.at(Index_stock_history_name)).toString());
        engine.SetTableCellString(table, i+2, 2, record.value(stock_history_name.at(Index_stock_history_unit)).toString());
        engine.SetTableCellString(table, i+2, 3, record.value(stock_history_name.at(Index_stock_history_operation)).toString());
        engine.SetTableCellString(table, i+2, 4, record.value(stock_history_name.at(Index_stock_history_count)).toString());
        engine.SetTableCellString(table, i+2, 5, record.value(stock_history_name.at(Index_stock_history_price)).toString());
    }

    QString word_file = "d:/操作清单_" + QDateTime::currentDateTime().toString(tr("yyyyMMdd_hhmm"));
    qDebug() << "word_file = " << word_file;
    engine.save(word_file);
    engine.close();
}
