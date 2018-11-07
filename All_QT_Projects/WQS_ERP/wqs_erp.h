#ifndef WQS_ERP_H
#define WQS_ERP_H

#include <QWidget>
#include <QtWidgets>
#include <QSqlTableModel>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlError>

#include <QList>

class wqs_erp : public QWidget
{
    Q_OBJECT
public:
    explicit wqs_erp(QWidget *parent = 0);

signals:

public slots:
    void slot_action_oparetion();
    void slot_action_search();
    void slot_action_button();
    void slot_action_statistics_word();

private:

    enum{
        Action_Push = 0,
        Action_Pop = 1,
        Action_Null = 2,
    };

    enum{
        Index_stock_name = 0,
        Index_stock_unit = 1,
        Index_stock_count = 2,
        Index_stock_remark = 3,
        Index_stock_history_name = 0,
        Index_stock_history_unit = 1,
        Index_stock_history_count = 2,
        Index_stock_history_price = 3,
        Index_stock_history_operation = 4,
        Index_stock_history_operation_time = 5,
        Index_stock_history_partner = 6,
        Index_stock_history_remark = 7,
    };
    QList<QString> stock_name = {
        "name",
        "unit",
        "count",
        "remark",
    };
    QList<QString> stock_name_china = {
        "品名规格",
        "单位",
        "数量",
        "备注",
    };
    QList<QString> stock_history_name = {
        "name",
        "unit",
        "count",
        "price",
        "operation",
        "operation_time",
        "partner",
        "remark",
    };
    QList<QString> stock_history_name_china = {
        "品名规格",
        "单位",
        "数量",
        "单价",
        "操作类型",
        "操作时间",
        "合作商",
        "备注",
    };

    void init_database();
    void init_model();
    void init_view();
    void init_layout();

    void statistics_total();
    void statistics_word();

    QTableView *data_view_stock;
    QTableView *data_view_stock_history;
    QSqlTableModel *data_model_stock;
    QSqlTableModel *data_model_stock_history;

    QPushButton* function_push;
    QPushButton* function_pop;
    QPushButton* function_history;

    QDateEdit *time_start;
    QDateEdit *time_end;

    QPushButton *action_push;
    QPushButton *action_search;
    QPushButton *action_statistics_word;

    QComboBox *search_stock_name;
    QLineEdit *search_text;

    QLabel *label_history_push_total;
    QLabel *label_history_pop_total;

    QLineEdit *lineedit_history_push_total;
    QLineEdit *lineedit_history_pop_total;


    int action_oparetion_type;
};

#endif // WQS_ERP_H
