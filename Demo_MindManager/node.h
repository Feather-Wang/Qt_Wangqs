#ifndef NODE_H
#define NODE_H

#include <QtGui>
#include <QGraphicsItem>

class Node : public QGraphicsItem
{
    /*宏，用来给类添加一个tr()函数*/
    Q_DECLARE_TR_FUNCTIONS(Node)

public:
    Node();
    ~Node();
    
    void setText(const QString &text);
    QString getText() const;
    QRectF nodeRect();

    /*在创建QGraphicsItem的子类时，要想自己实现绘图，一般是重新实现boundingRect()和paint()，boundingRect()是类QGraphicsItem中的纯虚函数，必须实现*/
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    
private:
    QString text;
};

#endif // NODE_H
