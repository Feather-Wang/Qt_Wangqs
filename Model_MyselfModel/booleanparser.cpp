#include "booleanparser.h"

#include <QtCore>

#include "booleanparser.h"
#include "BooleanItem.h"

BooleanParser::BooleanParser()
{

}

BooleanItem *BooleanParser::parse(const QString &expr)
{
    in = expr;
    in.replace(" ", "");
    pos = 0;

    BooleanItem *item = new BooleanItem(BooleanItem::Root);
    addChild(item, parseOrExpression());
    return item;
}

BooleanItem *BooleanParser::parseOrExpression()
{
    BooleanItem *childItem = parseAndExpression();
    if (matchToken("||"))
    {
        BooleanItem *item = new BooleanItem(BooleanItem::OrExpression);
        addChild(item, childItem);
        while (matchToken("||"))
        {
            addToken(item, "||", BooleanItem::Operator);
            addChild(item, parseAndExpression());
        }
        return item;
    }
    else
    {
        return childItem;
    }
}

BooleanItem *BooleanParser::parseAndExpression()
{
    BooleanItem *childItem = parseNotExpression();
    if (matchToken("&&"))
    {
        BooleanItem *item = new BooleanItem(BooleanItem::AndExpression);
        addChild(item, childItem);
        while (matchToken("&&"))
        {
            addToken(item, "&&", BooleanItem::Operator);
            addChild(item, parseNotExpression());
        }
        return item;
    }
    else
    {
        return childItem;
    }
}

BooleanItem *BooleanParser::parseNotExpression()
{
    if (matchToken("!"))
    {
        BooleanItem *item = new BooleanItem(BooleanItem::NotExpression);
        while (matchToken("!"))
            addToken(item, "!", BooleanItem::Operator);
        addChild(item, parseAtom());
        return item;
    }
    else
    {
        return parseAtom();
    }
}

BooleanItem *BooleanParser::parseAtom()
{
    if (matchToken("("))
    {
        BooleanItem *item = new BooleanItem(BooleanItem::Atom);
        addToken(item, "(", BooleanItem::Punctuator);
        addChild(item, parseOrExpression());
        addToken(item, ")", BooleanItem::Punctuator);
        return item;
    }
    else
    {
        return parseIdentifier();
    }
}

BooleanItem *BooleanParser::parseIdentifier()
{
    int startPos = pos;
    while (pos < in.length() && in[pos].isLetterOrNumber())
        ++pos;

    if (pos > startPos)
    {
        return new BooleanItem(BooleanItem::Identifier,
                        in.mid(startPos, pos - startPos));
    }
    else
    {
        return 0;
    }
}

void BooleanParser::addChild(BooleanItem *parent, BooleanItem *child)
{
    if (child)
    {
        parent->children += child;
        parent->str += child->str;
        child->parent = parent;
    }
}

void BooleanParser::addToken(BooleanItem *parent, const QString &str,
                             BooleanItem::Type type)
{
    if (in.mid(pos, str.length()) == str)
    {
        addChild(parent, new BooleanItem(type, str));
        pos += str.length();
    }
}

bool BooleanParser::matchToken(const QString &str) const
{
    return in.mid(pos, str.length()) == str;
}
