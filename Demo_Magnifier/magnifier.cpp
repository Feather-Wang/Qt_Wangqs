#include "magnifier.h"
#include <QtDebug>

#include <QMouseEvent>
#include <QScreen>
#include <QApplication>
#include <QPainter>

Magnifier::Magnifier(QWidget *parent)
    : QWidget(parent)
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    windowPixmap = QApplication::primaryScreen()->grabWindow(0);
}

Magnifier::~Magnifier()
{

}

void Magnifier::paintEvent(QPaintEvent *event)
{
    qDebug() << pos();
    /*放大倍率，200%就是0.5,400%就是0.25*/
    double beishu = 0.25;
    /*获取要显示的矩形的左上角的坐标，这个矩形的中心点事应用窗口部件的中心点*/
    QPoint p = pos() + QPoint(this->width()/2*(1-beishu), this->height()/2*(1-beishu));
    /*将要显示的矩形复制到copyPixmap中*/
    copyPixmap = windowPixmap.copy(QRect(p.x(), p.y(), this->width()*beishu, this->height()*beishu)).scaled(this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    /*在应用窗口部件中绘制copyPixmap*/
    QPainter painter(this);
    painter.drawPixmap(this->rect(), copyPixmap);
}

/*
每次鼠标点击要移动窗口时，保存开始移动时，应用窗口在桌面上的坐标
*/
void Magnifier::mousePressEvent(QMouseEvent *event)
{
    windowPixmap = QApplication::primaryScreen()->grabWindow(0);
    windowMoveStart = event->pos();
}

/*
这个事件的处理，主要是让应用在桌面上的位置，可以随着鼠标在应用上的移动而移动
*/
void Magnifier::mouseMoveEvent(QMouseEvent *event)
{
    /*首先用鼠标在应用中的当前坐标减去起始坐标，获取移动的差值，然后用这个差值+当前应用在桌面上的坐标，从而得到应用在桌面上的实际坐标*/
    QPoint p = event->pos() - windowMoveStart + pos();
    /*通过QWidget::move()将应用移动到计算出来的应用在桌面上的实际坐标p*/
    move(p);
    /*更新绘图*/
    update();
    /*调用默认的处理，完成其他的处理操作*/
    QWidget::mouseMoveEvent(event);
}

void Magnifier::enterEvent(QEvent *event)
{
    qDebug()<<"event=[" << event->type() << "]";
}
