#ifndef COLORNAMEDIALOG_H
#define COLORNAMEDIALOG_H

#include <QDialog>

class QStringListModel;
class QSortFilterProxyModel;
class QListView;
class QComboBox;
class QLineEdit;

class ColorNameDialog : public QDialog
{
    Q_OBJECT

public:
    ColorNameDialog(QWidget *parent = 0);
    ~ColorNameDialog();

public slots:
    void reapplyFilter();

private:
    QStringListModel *sourceModel;
    QSortFilterProxyModel *filterModel;
    QListView *listView;
    QComboBox *syntaxComboBox;
    QLineEdit *filterLineEdit;
};

#endif // COLORNAMEDIALOG_H
