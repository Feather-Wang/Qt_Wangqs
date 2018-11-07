/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtWidgets>
#include <QtDebug>

#include "mystyle.h"

MyStyle::MyStyle() :
    QProxyStyle(QStyleFactory::create("windows"))
{
}

/*
polish()和unpolish()函数会在安装或者卸载样式的时候得到调用。它们可以让我们对窗口部件（QWidget）或者调色板（QPalette）做适当的修改。
抛光（polishing）的概念在窗口部件中是通用的，当样式应用到窗口部件时，polish(QWidget *widget)就会得到调用，从而允许我们执行最后的定制。
unpolish()是用来取消polish()的作用。
polish()的一般做法是把样式子类作为窗口部件上的事件过滤器。这对于一些更高级的定制很有用。
*/
void MyStyle::polish(QPalette &palette)
{
    qDebug() << "polish(QPalette &palette)";

    QColor brown(212, 140, 95);
    QColor beige(236, 182, 120);
    QColor slightlyOpaqueBlack(0, 0, 0, 63);

    QPixmap backgroundImage(":/images/woodbackground.png");
    QPixmap buttonImage(":/images/woodbutton.png");
    QPixmap midImage = buttonImage;

    QPainter painter;
    painter.begin(&midImage);
    painter.setPen(Qt::NoPen);
    painter.fillRect(midImage.rect(), slightlyOpaqueBlack);
    painter.end();

    palette = QPalette(brown);

    palette.setBrush(QPalette::BrightText, Qt::white);
    palette.setBrush(QPalette::Base, beige);
    palette.setBrush(QPalette::Highlight, Qt::darkGreen);

    setTexture(palette, QPalette::Button, buttonImage);
    setTexture(palette, QPalette::Mid, midImage);
    setTexture(palette, QPalette::Window, backgroundImage);

    QBrush brush = palette.background();
    brush.setColor(brush.color().dark());

    palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
    palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
    palette.setBrush(QPalette::Disabled, QPalette::Mid, brush);
}

void MyStyle::polish(QWidget *widget)
{
    qDebug() << "polish(QWidget *widget)";

    /*这里判断是不是QPushButton按钮或者QComboBox菜单，设置它们的Qt::WA_Hover属性，当这一属性被设置、鼠标进入或者离开窗口部件所在区域时，就会产生一个绘制事件，可以让我们根据鼠标是否位于窗口部件上而把窗口部件绘制出不同的样子*/
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, true);
}

void MyStyle::unpolish(QWidget *widget)
{
    qDebug() << "unpolish(QWidget *widget)";

    /*当鼠标离开QPushButton或者QComboBox上方是，取消Qt::WA_Hover属性*/
    if (qobject_cast<QPushButton *>(widget)
            || qobject_cast<QComboBox *>(widget))
        widget->setAttribute(Qt::WA_Hover, false);
}

/*
pixelMetric()函数返回一个像素值，用于用户界面元素中。通过重新实现这个函数，既影响内置Qt窗口部件的绘制，也影响其尺寸。
*/
int MyStyle::pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const
{
    qDebug() << "pixelMetric(PixelMetric metric, const QStyleOption *option, const QWidget *widget) const";

    switch (metric)
    {
    case PM_ComboBoxFrameWidth:
        return 8;
    case PM_ScrollBarExtent:
        return QProxyStyle::pixelMetric(metric, option, widget) + 4;
    default:
        return QProxyStyle::pixelMetric(metric, option, widget);
    }
}


/*
返回一些关于样式外观的提示。styleHint()的返回值是int，对于不能用整数表示的少数的样式提示，styleHint()提供了一个指向QStyleHintReturn对象的指针。
*/
int MyStyle::styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const
{
    qDebug() << "styleHint(StyleHint hint, const QStyleOption *option, const QWidget *widget, QStyleHintReturn *returnData) const";

    switch (hint)
    {
    case SH_DitherDisabledText:
        return int(false);
    case SH_EtchDisabledText:
        return int(true);
    default:
        return QProxyStyle::styleHint(hint, option, widget, returnData);
    }
}

/*
用于绘制"基本的"用户界面元素，这些元素可能会被多个窗口部件使用，也可能被单个窗口部件使用。当一个窗口部件进行自身绘制的时候，都会调用该函数进行绘制自身的某个元素。
*/
void MyStyle::drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    qDebug() << "drawPrimitive(PrimitiveElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const";

    switch (element)
    {
    case PE_PanelButtonCommand:
        {
            int delta = (option->state & State_MouseOver) ? 64 : 0;
            QColor slightlyOpaqueBlack(0, 0, 0, 63);
            QColor semiTransparentWhite(255, 255, 255, 127 + delta);
            QColor semiTransparentBlack(0, 0, 0, 127 - delta);

            int x, y, width, height;
            option->rect.getRect(&x, &y, &width, &height);

            QPainterPath roundRect = roundRectPath(option->rect);

            int radius = qMin(width, height) / 2;

            QBrush brush;

            bool darker;

            const QStyleOptionButton *buttonOption = qstyleoption_cast<const QStyleOptionButton *>(option);
            if (buttonOption && (buttonOption->features & QStyleOptionButton::Flat))
            {
                brush = option->palette.background();
                darker = (option->state & (State_Sunken | State_On));
            }
            else
            {
                if (option->state & (State_Sunken | State_On))
                {
                    brush = option->palette.mid();
                    darker = !(option->state & State_Sunken);
                }
                else
                {
                    brush = option->palette.button();
                    darker = false;
                }
            }

            painter->save();

            painter->setRenderHint(QPainter::Antialiasing, true);

            painter->fillPath(roundRect, brush);

            if (darker)
                painter->fillPath(roundRect, slightlyOpaqueBlack);

            int penWidth;

            if (radius < 10)
                penWidth = 3;
            else if (radius < 20)
                penWidth = 5;
            else
                penWidth = 7;

            QPen topPen(semiTransparentWhite, penWidth);
            QPen bottomPen(semiTransparentBlack, penWidth);

            if (option->state & (State_Sunken | State_On))
                qSwap(topPen, bottomPen);

            int x1 = x;
            int x2 = x + radius;
            int x3 = x + width - radius;
            int x4 = x + width;

            if (option->direction == Qt::RightToLeft)
            {
                qSwap(x1, x4);
                qSwap(x2, x3);
            }

            QPolygon topHalf;
            topHalf << QPoint(x1, y)
                    << QPoint(x4, y)
                    << QPoint(x3, y + radius)
                    << QPoint(x2, y + height - radius)
                    << QPoint(x1, y + height);

            painter->setClipPath(roundRect);
            painter->setClipRegion(topHalf, Qt::IntersectClip);
            painter->setPen(topPen);
            painter->drawPath(roundRect);

            QPolygon bottomHalf = topHalf;
            bottomHalf[0] = QPoint(x4, y + height);

            painter->setClipPath(roundRect);
            painter->setClipRegion(bottomHalf, Qt::IntersectClip);
            painter->setPen(bottomPen);
            painter->drawPath(roundRect);

            painter->setPen(option->palette.foreground().color());
            painter->setClipping(false);
            painter->drawPath(roundRect);

            painter->restore();
        }
        break;

    default:
        QProxyStyle::drawPrimitive(element, option, painter, widget);
    }
}

void MyStyle::drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const
{
    qDebug() << "drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const";

    switch (element)
    {
    case CE_PushButtonLabel:
        {
            QStyleOptionButton myButtonOption;
            const QStyleOptionButton *buttonOption = qstyleoption_cast<const QStyleOptionButton *>(option);
            if (buttonOption)
            {
                myButtonOption = *buttonOption;
                if (myButtonOption.palette.currentColorGroup() != QPalette::Disabled)
                {
                    if (myButtonOption.state & (State_Sunken | State_On))
                    {
                        myButtonOption.palette.setBrush(QPalette::ButtonText, myButtonOption.palette.brightText());
                    }
                }
            }
            QProxyStyle::drawControl(element, &myButtonOption, painter, widget);
        }
        break;
    default:
        QProxyStyle::drawControl(element, option, painter, widget);
    }
}

void MyStyle::setTexture(QPalette &palette, QPalette::ColorRole role, const QPixmap &pixmap)
{
    //qDebug() << "setTexture(QPalette &palette, QPalette::ColorRole role, const QPixmap &pixmap)";

    for (int i = 0; i < QPalette::NColorGroups; ++i)
    {
        QColor color = palette.brush(QPalette::ColorGroup(i), role).color();
        palette.setBrush(QPalette::ColorGroup(i), role, QBrush(color, pixmap));
    }
}

QPainterPath MyStyle::roundRectPath(const QRect &rect)
{
    qDebug() << "roundRectPath(const QRect &rect)";

    int radius = qMin(rect.width(), rect.height()) / 2;
    int diam = 2 * radius;

    int x1, y1, x2, y2;
    rect.getCoords(&x1, &y1, &x2, &y2);

    QPainterPath path;
    path.moveTo(x2, y1 + radius);
    path.arcTo(QRect(x2 - diam, y1, diam, diam), 0.0, +90.0);
    path.lineTo(x1 + radius, y1);
    path.arcTo(QRect(x1, y1, diam, diam), 90.0, +90.0);
    path.lineTo(x1, y2 - radius);
    path.arcTo(QRect(x1, y2 - diam, diam, diam), 180.0, +90.0);
    path.lineTo(x1 + radius, y2);
    path.arcTo(QRect(x2 - diam, y2 - diam, diam, diam), 270.0, +90.0);
    path.closeSubpath();
    return path;
}
