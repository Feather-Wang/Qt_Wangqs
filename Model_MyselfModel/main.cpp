
#include <QApplication>
#include <QTableView>


void MyselfTableModel();
void MyselfTreeModel();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyselfTableModel();
    //MyselfTreeModel();

    return a.exec();
}

#include "currencymodel.h"
void MyselfTableModel()
{
    QMap<QString, double> currencyMap;
    currencyMap.insert("AUD", 1.3259);
    currencyMap.insert("CHF", 1.2970);
    currencyMap.insert("SGD", 1.6901);
    currencyMap.insert("USD", 1.0000);
    currencyMap.insert("QAD", 1.5351);

    CurrencyModel *model = new CurrencyModel;
    model->setCurrencyMap(currencyMap);


    QTableView *tableView = new QTableView;
    tableView->setModel(model);
    tableView->setAlternatingRowColors(true);
    tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    tableView->show();
}

#include "booleanwindow.h"
void MyselfTreeModel()
{
    BooleanWindow *window = new BooleanWindow;
    window->show();
}
