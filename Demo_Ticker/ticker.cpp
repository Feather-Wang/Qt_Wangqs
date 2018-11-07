#include <QtGui>
#include "ticker.h"

/*构造函数把offset变量初始化为0，用来绘制文本的x坐标值就取自于这个offset值，定时器的id通常是非零的，所以可以使用0来表示定时器还没有启动*/
Ticker::Ticker(QWidget *parent) : QWidget(parent)
{
    offset = 0;
    myTimerId = 0;
}

/*用来设置显示的文本，并且强制执行一个重绘操作*/
void Ticker::setText(const QString &newText)
{
    qDebug("setText()\n");
    myText = newText;
    update();
}

/*返回文本所需空间的大侠，以此作为窗口部件的理想大小*/
QSize Ticker::sizeHint() const
{
    qDebug("sizeHint()\n");
    return fontMetrics().size(0, text());
}

void Ticker::paintEvent(QPaintEvent *event)
{
    qDebug("paintEvent() = %d\n", width());
    QPainter painter(this);

    int textWidth = fontMetrics().width(text());
    qDebug("paintEvent() textwidth = %d, offset = %d\n", textWidth, offset);
    if( textWidth < 1 )
        return;

    int x = -offset;
    while( x < width() )
    {
        qDebug("paintEvent() x = %d\n", x);
        painter.drawText(x, 0, textWidth, height(), Qt::AlignLeft | Qt::AlignVCenter, text());
        x += textWidth;
    }
}

/*用来启动一个定时器，startTimer()会返回一个ID数字，可以在以后用这个数字识别该定时器，大约每30秒会产生一个定时器事件。
 * 本可以在构造函数中调用startTimer()，但是只有在窗口部件实际可见的时候，才有必要保存由Qt产生的定时器事件的那些资源。
*/
void Ticker::showEvent(QShowEvent *event)
{
    qDebug("showEvent()\n");
    myTimerId = startTimer(30);
}

void Ticker::timerEvent(QTimerEvent *event)
{
    qDebug("timerEvent()\n");
    if( event->timerId() == myTimerId )
    {
        ++offset;
        if( offset >= fontMetrics().width(text()) )
            offset = 0;
        scroll(-1, 0);
    }
    else
    {
        QWidget::timerEvent(event);
    }
}

/*停止定时器*/
void Ticker::hideEvent(QHideEvent *event)
{
    qDebug("hideEvent()\n");
    killTimer(myTimerId);
    myTimerId = 0;
}
