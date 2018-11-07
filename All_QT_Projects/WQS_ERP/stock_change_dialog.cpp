#include "stock_change_dialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>

stock_change_dialog::stock_change_dialog(int type, QWidget *parent)
    :QDialog(parent)
{
    label_name.setText(tr("品名规格"));
    label_name.setFixedWidth(100);
    label_unit.setText(tr("单位"));
    label_unit.setFixedWidth(100);
    label_price.setText(tr("单价"));
    label_price.setFixedWidth(100);
    label_remark.setText(tr("备注"));
    label_remark.setFixedWidth(100);
    if( type == Action_Type_Push )
        label_count.setText(tr("入库数量"));
    else
        label_count.setText(tr("出库数量"));
    label_count.setFixedWidth(100);
    label_partner.setText(tr("合作商"));
    label_partner.setFixedWidth(100);


    QHBoxLayout *layout_name = new QHBoxLayout;
    layout_name->addWidget(&label_name);
    layout_name->addWidget(&edit_name);

    QHBoxLayout *layout_unit = new QHBoxLayout;
    layout_unit->addWidget(&label_unit);
    layout_unit->addWidget(&edit_unit);

    QHBoxLayout *layout_price = new QHBoxLayout;
    layout_price->addWidget(&label_price);
    layout_price->addWidget(&edit_price);

    QHBoxLayout *layout_count = new QHBoxLayout;
    layout_count->addWidget(&label_count);
    layout_count->addWidget(&edit_count);

    QHBoxLayout *layout_partner = new QHBoxLayout;
    layout_partner->addWidget(&label_partner);
    layout_partner->addWidget(&edit_partner);

    QHBoxLayout *layout_remark = new QHBoxLayout;
    layout_remark->addWidget(&label_remark);
    layout_remark->addWidget(&edit_remark);

    button_cancel.setText(tr("取消"));
    button_accept.setText(tr("确认"));
    connect(&button_cancel, SIGNAL(clicked(bool)), this, SLOT(close()));
    connect(&button_accept, SIGNAL(clicked(bool)), this, SLOT(accept()));
    QHBoxLayout *layout_button = new QHBoxLayout;
    layout_button->addWidget(&button_cancel);
    layout_button->addWidget(&button_accept);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(layout_name);
    layout->addLayout(layout_unit);
    layout->addLayout(layout_price);
    layout->addLayout(layout_count);
    layout->addLayout(layout_partner);
    layout->addLayout(layout_remark);
    layout->addLayout(layout_button);

    setLayout(layout);
}

QString stock_change_dialog::getName()
{
    return edit_name.text();
}

QString stock_change_dialog::getUnit()
{
    return edit_unit.text();
}

double stock_change_dialog::getPrice()
{
    return edit_price.text().toDouble();
}

int stock_change_dialog::getCount()
{
    return edit_count.text().toInt();
}

QString stock_change_dialog::getPartner()
{
    return edit_partner.text();
}

QString stock_change_dialog::getRemark()
{
    return edit_remark.text();
}

void stock_change_dialog::setName(const QString &name)
{
    edit_name.setText(name);
    edit_name.setEnabled(false);
}

void stock_change_dialog::setUnit(const QString &unit)
{
    edit_unit.setText(unit);
    edit_unit.setEnabled(false);
}

void stock_change_dialog::setHideLabel(int type)
{
    switch (type) {
    case Index_Name:
        label_name.hide();
        edit_name.hide();
        break;
    case Index_Unit:
        label_unit.hide();
        edit_unit.hide();
        break;
    case Index_Price:
        label_price.hide();
        edit_price.hide();
        break;
    case Index_Count:
        label_count.hide();
        edit_count.hide();
        break;
    case Index_Partner:
        label_partner.hide();
        edit_partner.hide();
        break;
    case Index_Remark:
        label_remark.hide();
        edit_remark.hide();
        break;
    default:
        break;
    }
}
