#include "colornamedialog.h"

#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QListView>
#include <QComboBox>
#include <QLineEdit>

#include <QVBoxLayout>

ColorNameDialog::ColorNameDialog(QWidget *parent)
    : QDialog(parent)
{
    /*创建QStringListModel模型，存储颜色列表*/
    sourceModel = new QStringListModel;
    sourceModel->setStringList(QColor::colorNames());

    /*创建QSortFilterProxyModel模型，将QStringListModel模型设置为被管理模型，并且过滤列设置为序号为0的列*/
    filterModel = new QSortFilterProxyModel;
    filterModel->setSourceModel(sourceModel);
    filterModel->setFilterKeyColumn(0);

    /*创建QListView对象，与QSortFilterProxyModel模型关联起来*/
    listView = new QListView;
    listView->setModel(filterModel);

    /*创建QLineEdit对象，用于输入过滤字符串*/
    filterLineEdit = new QLineEdit;

    /*创建QComboBox对象，用于存储过滤方式*/
    syntaxComboBox = new QComboBox;
    syntaxComboBox->addItem(tr("Regular expression"), QRegExp::RegExp);
    syntaxComboBox->addItem(tr("Wildcard"), QRegExp::Wildcard);
    syntaxComboBox->addItem(tr("Fixed string"), QRegExp::FixedString);

    /*布局管理器*/
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(listView);
    layout->addWidget(filterLineEdit);
    layout->addWidget(syntaxComboBox);

    setLayout(layout);

    /*将QLIneEdit对象的内容改变信号，与自定义槽reappleFilter()关联起来*/
    connect(filterLineEdit, SIGNAL(textChanged(QString)), this, SLOT(reapplyFilter()));
}

ColorNameDialog::~ColorNameDialog()
{

}

/*
获取QComboBox内的过滤方式，创建QregExp::PatternSyntax过滤对象，
然后将过滤对象，设置到QSortFilterProxyModel模型中，由QSortFilterProxyModel模型完成对被管理模型QStringListModel模型的过滤操作以及刷新显示。
*/
void ColorNameDialog::reapplyFilter()
{
    QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(syntaxComboBox->itemData(syntaxComboBox->currentIndex()).toInt());
    QRegExp regExp(filterLineEdit->text(), Qt::CaseInsensitive, syntax);
    filterModel->setFilterRegExp(regExp);
}
