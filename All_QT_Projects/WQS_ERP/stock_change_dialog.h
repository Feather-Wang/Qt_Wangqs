#ifndef STOCK_CHANGE_DIALOG_H
#define STOCK_CHANGE_DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class stock_change_dialog : public QDialog
{
public:
    stock_change_dialog(int type, QWidget *parent = 0);

    QString getName();
    QString getUnit();
    double getPrice();
    int getCount();
    QString getPartner();
    QString getRemark();

    void setName(const QString &name);
    void setUnit(const QString &unit);
    void setHideLabel(int type);

    enum
    {
        Action_Type_Push = 0,
        Action_Type_Pop = 1,

        Index_Name = 0,
        Index_Unit = 1,
        Index_Price = 2,
        Index_Count = 3,
        Index_Partner = 4,
        Index_Remark = 5,
    };

private:
    QLabel label_name;
    QLabel label_unit;
    QLabel label_price;
    QLabel label_count;
    QLabel label_partner;
    QLabel label_remark;

    QLineEdit edit_name;
    QLineEdit edit_unit;
    QLineEdit edit_price;
    QLineEdit edit_count;
    QLineEdit edit_partner;
    QLineEdit edit_remark;

    QPushButton button_accept;
    QPushButton button_cancel;
};

#endif // STOCK_CHANGE_DIALOG_H
