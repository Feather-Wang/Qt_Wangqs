#ifndef BOOLEANITEM_H
#define BOOLEANITEM_H

#include <QString>
#include <QList>

/*模型中，每一项的数据*/
class BooleanItem
{
public:
    enum Type { Root, OrExpression, AndExpression, NotExpression, Atom, Identifier, Operator, Punctuator };

    BooleanItem(Type type, const QString &str = "");
    ~BooleanItem();

    /*数据的类型*/
    Type type;
    /*数据的内容*/
    QString str;
    /*指向父项*/
    BooleanItem *parent;
    /*指向子项*/
    QList<BooleanItem *> children;
};

#endif // BOOLEANITEM_H
