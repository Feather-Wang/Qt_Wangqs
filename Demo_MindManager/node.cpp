#include "node.h"

#include <QtGui>
#include <QStyleOptionGraphicsItem>
#include <QInputDialog>
#include <QGraphicsSceneMouseEvent>

Node::Node()
{
    setFlags(ItemIsMovable | ItemIsSelectable);
}

Node::~Node()
{
    qDebug("jiexi\n");
}

void Node::setText(const QString &text)
{
    this->text = text;
}

QString Node::getText() const
{
    return text;
}

QRectF Node::boundingRect() const
{
    const int Margin = 1;
    //return nodeRect().adjusted(-Margin, -Margin, +Margin, +Margin);
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = nodeRect();
    painter->drawRoundRect(rect, rect.width(), rect.height());

    /*最后，在圆角矩形的上面绘制文字，使其居中与边缘矩形*/
    painter->drawText(rect, Qt::AlignCenter, text);
}

/*如果用户双击该节点，就弹出一个显示当前文字的对话框，并且允许用户修改它。
 * 如果用户点击Cancel，将会返回一个空字符串，因此，只有当字符串不为空时，这个修改才会有效
*/
void Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QString text = QInputDialog::getText(event->widget(),
                           tr("Edit Text"), tr("Enter new text:"),
                           QLineEdit::Normal, this->text);
    if (!text.isEmpty())
        setText(text);
}

/*一旦用户拖动一个节点，就会调用itemChange()处理器*/
QVariant Node::itemChange(GraphicsItemChange change,
                          const QVariant &value)
{
    /*最后，调用基类的实现以确保基类也得到了通知*/
    return QGraphicsItem::itemChange(change, value);
}

QRectF Node::nodeRect()
{
    const int Padding = 8;
    QFontMetricsF metrics(qApp->font());
    QRectF rect = metrics.boundingRect(text);
    rect.adjust(-Padding, -Padding, +Padding, +Padding);
    rect.translate(-rect.center());
    return rect;
}
