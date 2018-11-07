#ifndef NODE_H
#define NODE_H

#include <QtGui>
#include <QGraphicsItem>
class Link;


class Node : public QGraphicsItem
{
    /*宏，用来给类添加一个tr()函数*/
    Q_DECLARE_TR_FUNCTIONS(Node)

public:
    Node();
    ~Node();

    void setText(const QString &text);
    QString text() const;
    void setTextColor(const QColor &color);
    QColor textColor() const;
    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;
    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void addLink(Link *link);
    void removeLink(Link *link);

    /*在创建QGraphicsItem的子类时，要想自己实现绘图，一般是重新实现boundingRect()和paint()*/
    QRectF boundingRect() const;
    /*由QGraphicsView调用，用来做精确的碰撞检测。通常，可以忽略它，由项基于外接矩形自行计算形状，这里重新实现了它，尤其返回一个QPainterPath对象，代表了一个圆角矩形*/
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    /*返回结点绘制的矩形*/
    QRectF outlineRect() const;
    /*返回一个基于矩形宽度和高度的合适的圆度系数*/
    int roundness(double size) const;

    QSet<Link *> myLinks;
    QString myText;
    QColor myTextColor;
    QColor myBackgroundColor;
    QColor myOutlineColor;
};

#endif // NODE_H
