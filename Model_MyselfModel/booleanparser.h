#ifndef BOOLEANPARSER_H
#define BOOLEANPARSER_H

#include "BooleanItem.h"
#include <QString>

class BooleanParser
{
public:
    BooleanParser();

public:
    BooleanItem *parse(const QString &expr);

private:
    BooleanItem *parseOrExpression();
    BooleanItem *parseAndExpression();
    BooleanItem *parseNotExpression();
    BooleanItem *parseAtom();
    BooleanItem *parseIdentifier();
    void addChild(BooleanItem *parent, BooleanItem *child);
    void addToken(BooleanItem *parent, const QString &str, BooleanItem::Type type);
    bool matchToken(const QString &str) const;

    QString in;
    int pos;
};

#endif // BOOLEANPARSER_H
