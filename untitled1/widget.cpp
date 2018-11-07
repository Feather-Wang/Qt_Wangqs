#include "widget.h"
#include <QPainter>
#include <QPaintEvent>
#include <QLinearGradient>
#include <QtDebug>

#define HEAD_HEIGHT 50
#define HEAD_SPACE  10

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::HighQualityAntialiasing|QPainter::Antialiasing);

    // 绘制item区域

    qreal nItemY = 0;
    /*获得窗口的宽度*/
    int nWidth = this->width();
    nWidth = (0 == nWidth % 2) ? nWidth : nWidth + 1;

    QPointF topLeft(0,nItemY);
    QPointF bottomRight(nWidth, nItemY + HEAD_HEIGHT + HEAD_SPACE);
    QRectF ItemRect(topLeft,bottomRight);
    qDebug() << ItemRect.center().x() << ItemRect.center().y() << nWidth;

    /*移动窗口部件的坐标系，x轴向右移动一半，y轴，向下移动一条记录的一半大小*/
    QTransform t;
    t.translate(ItemRect.center().x(),ItemRect.center().y());
    painter.setTransform(t);

    QPointF rectTopLeft;
    QPointF rectBottomRight;
    QRectF textRect(rectTopLeft,rectBottomRight);

    /*设置字体，字体大小，以及显示的内容*/
    QFont font("幼圆", 10);
    painter.setFont(font);
    QString strText = "wangqingsong1234678901234567890987654123451111111122222222233333333333444444444555555555555";

    // 计算文字的宽度和高度
    QFontMetrics fm(font);
    int pixelsWide = fm.width(strText);
    int pixelsHigh = fm.height();
    /*字体部分的宽度和高度*/
    pixelsWide = pixelsWide < (nWidth * 2 / 3) ? pixelsWide: (nWidth * 2 / 3);
    pixelsHigh = pixelsWide < (nWidth * 2 / 3) ? HEAD_HEIGHT : (((pixelsWide / (nWidth / 2)) + 1) * HEAD_HEIGHT / 2);

    if( 1 )
    {
        // 绘制头像
        painter.drawPixmap(nWidth / 2 - 54, -HEAD_HEIGHT / 2 + 1, 48, 48, QPixmap(":/images/head.jpg"));

        // 计算右边的宽度x
        int nX = (nWidth / 2) - 85 - pixelsWide;
        if (nX < 0)
        {
            nX = -pixelsWide - 85 + nWidth / 2;
        }
        // 计算气泡框
        textRect = QRectF(nX, -HEAD_HEIGHT / 2, pixelsWide + 20, pixelsHigh);

        // 计算气泡右边的三角
        QPainterPath path;
        path.addRoundedRect(textRect, 10, 10);
        path.moveTo(nWidth / 2 - 65, -HEAD_HEIGHT / 2 + 10);
        path.lineTo(nWidth / 2 - 55, -HEAD_HEIGHT / 2 + 16);
        path.lineTo(nWidth / 2 - 65, -HEAD_HEIGHT / 2 + 19);
        painter.fillPath(path, QColor("#3FA7EC"));

        // 重新调整文字区域
        textRect = QRectF(nX + 10, -HEAD_HEIGHT / 2, pixelsWide, pixelsHigh);
    }
    else
    {
        // 绘制气泡区域
        textRect = QRectF(-nWidth / 2 + 65, -HEAD_HEIGHT / 2, pixelsWide + 20, pixelsHigh);
        // 左边三角
        QPainterPath path;
        path.addRoundedRect(textRect, 5, 5);
        path.moveTo(-nWidth / 2 + 65, -HEAD_HEIGHT / 2 + 10 );
        path.lineTo(-nWidth / 2 + 55, -HEAD_HEIGHT / 2 + 16);
        path.lineTo(-nWidth / 2 + 65, -HEAD_HEIGHT / 2 + 19);
        painter.fillPath(path, QColor("#E2A3E2"));

        // 绘制头像
        painter.drawPixmap(-nWidth/2 + 6, -HEAD_HEIGHT / 2 + 1, 48, 48, QPixmap(":/images/head.jpg"));

        // 绘制文字区域
        textRect = QRectF(-nWidth / 2 + 65 + 10, -HEAD_HEIGHT / 2, pixelsWide, pixelsHigh);
    }

    painter.drawText(textRect, strText, Qt::AlignVCenter |Qt::AlignLeft);
}
