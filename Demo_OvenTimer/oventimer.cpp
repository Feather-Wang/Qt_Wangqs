#include "oventimer.h"

#include <QtGui>

const double DegreesPerMinute = 7.0;
const double DegreesPerSecond = DegreesPerMinute / 60;
const int MaxMinutes = 45;
const int MaxSeconds = MaxMinutes * 60;
const int UpdateInterval = 5;

OvenTimer::OvenTimer(QWidget *parent) : QWidget(parent)
{
    finishTime = QDateTime::currentDateTime();
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(update()));

    finishTimer = new QTimer(this);
    finishTimer->setSingleShot(true);
    connect(finishTimer, SIGNAL(timeout()), this, SIGNAL(timeout()));
    connect(finishTimer, SIGNAL(timeout()), updateTimer, SLOT(stop()));

    /*将字体大小设置为8磅*/
    QFont font;
    font.setPointSize(8);
    setFont(font);
}

void OvenTimer::setDuration(int secs)
{
    /*
     * qBound()等同于以下代码
     * if( secs < 0 )
     * {
     *      secs = 0;
     * }
     * else if( secs > MaxSeconds )
     * {
     *      secs = MaxSeconds;
     * }
     */
    secs = qBound(0, secs, MaxSeconds);

    finishTime = QDateTime::currentDateTime().addSecs(secs);

    if( secs > 0 )
    {
        /*启动定时器，间隔时间*/
        updateTimer->start(UpdateInterval * 1000);
        finishTimer->start(secs * 1000);
    }
    else
    {
        updateTimer->stop();
        finishTimer->stop();
    }

    update();
}

int OvenTimer::duration() const
{
    int secs = QDateTime::currentDateTime().secsTo(finishTime);
    if( secs < 0 )
        secs = 0;
    return secs;
}

/*当用户点击窗口部件时，找到最近的刻度*/
void OvenTimer::mousePressEvent(QMouseEvent *event)
{
    QPointF point = event->pos() - rect().center();
    double theta = std::atan2(-point.x(), -point.y()) * 180.0 / M_PI;
    setDuration(duration() + int(theta / DegreesPerSecond));
    update();
}

/*把视口设置成窗口部件中最大的正方形，把窗口设置成（-50,-50,100,100）的矩形*/
void OvenTimer::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    /*返回两个参数中最小的一个*/
    int side = qMin(width(), height());

    painter.setViewport((width() - side) / 2, (height() - side) / 2, side, side);
    painter.setWindow(-50, -50, 100, 100);

    /*执行绘图*/
    draw(&painter);
}

void OvenTimer::draw(QPainter *painter)
{
    static const int triangle[3][2] = { {-2,-49}, {+2, -49}, {0, -47} };
    QPen thickPen(palette().foreground(), 1.5);
    QPen thinPen(palette().foreground(), 0.5);
    QColor niceBlue(150, 150, 200);

    /*首先在窗口部件顶部的0位置绘制一个小三角形，这个小三角形的三个坐标都是由代码直接给定*/
    painter->setPen(thinPen);
    painter->setBrush(palette().foreground());
    painter->drawPolygon(QPolygon(3, &triangle[0][0]));

    /*绘制外面的圆，然后用锥形渐变填充，锥形的中心点位于（0,0），角度是-90度*/
    QConicalGradient coneGradient(0, 0, -90.0);
    coneGradient.setColorAt(0.0, Qt::darkGray);
    coneGradient.setColorAt(0.2, niceBlue);
    coneGradient.setColorAt(0.5, Qt::white);
    coneGradient.setColorAt(1.0, Qt::darkGray);

    painter->setBrush(coneGradient);
    painter->drawEllipse(-46, -46, 92, 92);

    /*我们用辐射渐变填充内部的圆，渐变的中心点和焦点都在（0,0），渐变的半径是20*/
    QRadialGradient haloGradient(0, 0, 20, 0, 0);
    haloGradient.setColorAt(0.0, Qt::lightGray);
    haloGradient.setColorAt(0.8, Qt::darkGray);
    haloGradient.setColorAt(0.9, Qt::white);
    haloGradient.setColorAt(1.0, Qt::black);

    painter->setPen(Qt::NoPen);
    painter->setBrush(haloGradient);
    painter->drawEllipse(-20, -20, 40, 40);

    /*
     * 调用rotate()来旋转绘图器的坐标系统
     */
    QLinearGradient knobGradient(-7, -25, 7, -25);
    knobGradient.setColorAt(0.0, Qt::black);
    knobGradient.setColorAt(0.2, niceBlue);
    knobGradient.setColorAt(0.3, Qt::lightGray);
    knobGradient.setColorAt(0.8, Qt::white);
    knobGradient.setColorAt(1.0, Qt::black);

    painter->rotate(duration() * DegreesPerSecond);
    painter->setBrush(knobGradient);
    painter->setPen(thinPen);
    painter->drawRoundRect(-7, -25, 14, 50, 99, 49);

    for( int i = 0; i <= MaxMinutes; ++i)
    {
        painter->save();
        painter->rotate(-i * DegreesPerMinute);

        if( i % 5 == 0 )
        {
            painter->setPen(thickPen);
            painter->drawLine(0, -41, 0, -44);
            painter->drawText(-15, -41, 30, 30, Qt::AlignHCenter | Qt::AlignTop, QString::number(i));
        }
        else
        {
            painter->setPen(thinPen);
            painter->drawLine(0, -42, 0, -44);
        }

        painter->restore();
    }
}
