#include <QtGui>

#include "sortdialog.h"

SortDialog::SortDialog(QWidget *parent)
    :QDialog(parent)
{
    setupUi(this);

    /*将secondaryGroupBox和tertiaryGroupBox初始化为隐藏状态*/
    secondaryGroupBox->hide();
    tertiaryGroupBox->hide();

    /*这样会使用户不能再重新修改这个对话框窗体的大小，这样一来，布局就会负责对话框重新定义大小的职责，并且也会在显示或隐藏子窗口部件的时候自动重新定义这个对话框的大小，从而可以确保对话框总是能以最佳的尺寸显示出来*/
    layout()->setSizeConstraint(QLayout::SetFixedSize);

    setColumnRange('A', 'Z');
}

void SortDialog::setColumnRange(QChar first, QChar last)
{
    primaryColumnCombo->clear();
    secondaryColumnCombo->clear();
    tertiaryColumnCombo->clear();

    secondaryColumnCombo->addItem(tr("None"));
    tertiaryColumnCombo->addItem(tr("None"));
    primaryColumnCombo->setMinimumSize(secondaryColumnCombo->sizeHint());

    QChar ch = first;
    while( ch <= last )
    {
        primaryColumnCombo->addItem(QString(ch));
        secondaryColumnCombo->addItem(QString(ch));
        tertiaryColumnCombo->addItem(QString(ch));

        ch = ch.unicode() + 1;
    }
}
