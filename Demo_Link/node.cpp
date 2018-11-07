#include <QtGui>

#include "link.h"
#include "node.h"

#include <QStyleOptionGraphicsItem>
#include <QInputDialog>
#include <QGraphicsSceneMouseEvent>

/*初始化颜色，设置节点可被移动和选取*/
Node::Node()
{
    myTextColor = Qt::darkGreen;
    myOutlineColor = Qt::darkBlue;
    myBackgroundColor = Qt::white;

    setFlags(ItemIsMovable | ItemIsSelectable);
}

Node::~Node()
{
    foreach (Link *link, myLinks)
        delete link;
}

void Node::setText(const QString &text)
{
    prepareGeometryChange();
    myText = text;
    update();
}

QString Node::text() const
{
    return myText;
}

void Node::setTextColor(const QColor &color)
{
    myTextColor = color;
    update();
}

QColor Node::textColor() const
{
    return myTextColor;
}

void Node::setOutlineColor(const QColor &color)
{
    myOutlineColor = color;
    update();
}

QColor Node::outlineColor() const
{
    return myOutlineColor;
}

void Node::setBackgroundColor(const QColor &color)
{
    myBackgroundColor = color;
    update();
}

QColor Node::backgroundColor() const
{
    return myBackgroundColor;
}

void Node::addLink(Link *link)
{
    myLinks.insert(link);
}

void Node::removeLink(Link *link)
{
    myLinks.remove(link);
}

QRectF Node::boundingRect() const
{
    const int Margin = 1;
    return outlineRect().adjusted(-Margin, -Margin, +Margin, +Margin);
}

QPainterPath Node::shape() const
{
    QRectF rect = outlineRect();

    QPainterPath path;
    path.addRoundRect(rect, roundness(rect.width()),
                      roundness(rect.height()));
    return path;
}

/*
 * 绘制项
 * 如果项被选中，就将画笔的风格改为点线型，而且使线更粗些，否则，默认使用像素为1的实线，还设置了画刷为背景色
 */
void Node::paint(QPainter *painter,
                 const QStyleOptionGraphicsItem *option,
                 QWidget * /* widget */)
{
    /*QStyleOptionGraphicsItem类是Qt的一个不寻常的类，因为它提供了几个公有成员变量。
     * 这包括当前的布局方向、字体规格、调色板、矩形、状态（如选中、获取焦点，以及其它一些状态等）、变换矩阵和细节级别。
     * 这里我们检查了状态变量来确定节点是否被选中。
     */
    QPen pen(myOutlineColor);
    if (option->state & QStyle::State_Selected) {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }
    painter->setPen(pen);
    /*设置了画刷为背景色*/
    painter->setBrush(myBackgroundColor);

    /*绘制一个与边缘矩形大小相等的圆角矩形，其中使用了由roundness()私有函数返回的圆角率*/
    QRectF rect = outlineRect();
    painter->drawRoundRect(rect, roundness(rect.width()),
                           roundness(rect.height()));

    /*最后，在圆角矩形的上面绘制文字，使其居中与边缘矩形*/
    painter->setPen(myTextColor);
    painter->drawText(rect, Qt::AlignCenter, myText);
}

/*如果用户双击该节点，就弹出一个显示当前文字的对话框，并且允许用户修改它。
 * 如果用户点击Cancel，将会返回一个空字符串，因此，只有当字符串不为空时，这个修改才会有效
*/
void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QString text = QInputDialog::getText(event->widget(),
                           tr("Edit Text"), tr("Enter new text:"),
                           QLineEdit::Normal, myText);
    if (!text.isEmpty())
        setText(text);
}

/*一旦用户拖动一个节点，就会调用itemChange()处理器*/
QVariant Node::itemChange(GraphicsItemChange change,
                          const QVariant &value)
{
    /*为了保证Link处于正确的位置，可以遍历节点的Link集合，通知每一条线更新它们的端点*/
    if (change == ItemPositionHasChanged) {
        foreach (Link *link, myLinks)
            link->trackNodes();
    }
    /*最后，调用基类的实现以确保基类也得到了通知*/
    return QGraphicsItem::itemChange(change, value);
}

QRectF Node::outlineRect() const
{
    const int Padding = 8;
    QFontMetricsF metrics(qApp->font());
    QRectF rect = metrics.boundingRect(myText);
    rect.adjust(-Padding, -Padding, +Padding, +Padding);
    rect.translate(-rect.center());
    return rect;
}

/*返回合适的圆角率，确保节点的转角是直径为12的四分之一圆*/
int Node::roundness(double size) const
{
    const int Diameter = 12;
    return 100 * Diameter / int(size);
}
