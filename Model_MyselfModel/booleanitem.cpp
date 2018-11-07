#include "booleanitem.h"
#include <QtGlobal>
BooleanItem::BooleanItem(Type type, const QString &str)
{
    this->type = type;
    this->str = str;
    parent = 0;
}

BooleanItem::~BooleanItem()
{
    qDeleteAll(children);
}
