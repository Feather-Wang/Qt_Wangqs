#ifndef WATCH_H
#define WATCH_H

#include <QWidget>

class QTimer;

class Watch : public QWidget
{
    Q_OBJECT
public:
    explicit Watch(QWidget *parent = 0);

protected:
    /*绘制表的表盘，指针*/
    void paintEvent(QPaintEvent *);
    /*返回窗口的大小，为了更好的定位坐标，这里返回的长度和宽度都是奇数*/
    QSize sizeHint() const;

signals:

public slots:
    /*用于响应计时器，然后处理时针、分针、秒针的旋转角度*/
    void timeupdate();
private:
    /*定时器*/
    QTimer *timer;
    /*分别保存时针、分针、秒针的旋转角度*/
    int rotate_hour;
    int rotate_mini;
    int rotate_sec;
};

#endif // WATCH_H
