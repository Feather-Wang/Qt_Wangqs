#ifndef LINK_H
#define LINK_H

#include <QGraphicsLineItem>

class Node;

/*用于保存一条线的数据，起始结点，结束结点，颜色*/
class Link : public QGraphicsLineItem
{
    Q_OBJECT

public:
    Link(Node *fromNode, Node *toNode);
    ~Link();

    Node *fromNode() const;
    Node *toNode() const;

    void setColor(const QColor &color);
    QColor color() const;

    /*用来更新先的端点*/
    void trackNodes();

private:
    Node *myFromNode;
    Node *myToNode;
};

#endif // LINK_H
