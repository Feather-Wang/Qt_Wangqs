#include "watch.h"
#include <QtDebug>

#include <QTimer>
#include <QPaintEvent>
#include <QPainter>
#include <QImage>
#include <QTransform>

Watch::Watch(QWidget *parent) : QWidget(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    /*创建定时器，并将定时器的超时信号和自定义槽处理函数绑定在一起，启动定时器，间隔时间为1s*/
    timer = new QTimer;
    connect(timer, SIGNAL(timeout()), SLOT(timeupdate()));
    timer->start(100);
    /*时针、分针、秒针的旋转角度初始化为0*/
    rotate_hour = 0;
    rotate_mini = 0;
    rotate_sec = 0;
}

QSize Watch::sizeHint() const
{
    /*窗口的大小为(501,501)，方便定位坐标*/
    return QSize(501, 501);
}

/*生成时针、分针、秒针的旋转角度逻辑，然后调用update()生成一个绘制事件*/
void Watch::timeupdate()
{
    if( rotate_mini == 354 && rotate_sec == 354 )
    {
        rotate_hour += 360 / 12;
        if( rotate_hour == 360 )
            rotate_hour = 0;
    }

    if( rotate_sec == 354 )
    {
        rotate_mini += 6;
        if( rotate_mini == 360 )
            rotate_mini = 0;
    }

    rotate_sec += 6;
    if( rotate_sec == 360 )
        rotate_sec = 0;

    qDebug() << rotate_hour << rotate_mini << rotate_sec;
    update();
}

void Watch::paintEvent(QPaintEvent *)
{
    /*首先，定义一个窗口坐标系移动策略，将坐标系的原点（0,0）移动到窗口中心*/
    QTransform transform;
    transform.translate(251, 251);

    QPainter painter(this);
    /*开启反走样，使用transform*/
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setTransform(transform);
    /*加载表盘图片，然后计算图片的左上角的坐标，因为要让表盘中心和坐标系(0,0)重合*/
    QImage watch(":/images/watch_new.png");
    qreal watch_center_w = 0 - watch.width() / 2 - watch.width() % 2;
    qreal watch_center_h = 0 - watch.height() / 2 - watch.height() % 2;
    /*加载时针图片，然后计算图片的左上角的坐标，因为要让时针的某一点和坐标系(0,0)重合*/
    QImage hour(":/images/hour_pointer.png");
    qreal hour_center_w = 0 - hour.width() / 2 - hour.width() % 2;
    qreal hour_center_h = 0 - hour.height() / 2 - hour.height() % 2 - 67;
    /*加载分针图片，然后计算图片的左上角的坐标，因为要让时针的某一点和坐标系(0,0)重合*/
    QImage mini(":/images/mini_pointer.png");
    qreal mini_center_w = 0 - mini.width() / 2 - mini.width() % 2;
    qreal mini_center_h = 0 - mini.height() / 2 - mini.height() % 2 - 84;
    /*加载秒针图片，然后计算图片的左上角的坐标，因为要让时针的某一点和坐标系(0,0)重合*/
    QImage sec(":/images/sec_pointer.png");
    qreal sec_center_w = 0 - sec.width() / 2 - sec.width() % 2 - 1;
    qreal sec_center_h = 0 - sec.height() / 2 - sec.height() % 2 - 62.5;

    /*绘制表盘*/
    painter.drawImage(watch_center_w, watch_center_h, watch);
    /*绘制时针，这里使用save和restore，下面绘制分针、秒针时也是用了，这是因为如果不这么做的话，它们自身的旋转会影响彼此*/
    painter.save();
    painter.rotate(rotate_hour);
    painter.drawImage(hour_center_w, hour_center_h, hour);
    painter.restore();
    /*绘制分针*/
    painter.save();
    painter.rotate(rotate_mini);
    painter.drawImage(mini_center_w, mini_center_h, mini);
    painter.restore();
    /*绘制秒针*/
    painter.save();
    painter.rotate(rotate_sec);
    painter.drawImage(sec_center_w, sec_center_h, sec);
    painter.restore();
}
