#ifndef MAGNIFIER_H
#define MAGNIFIER_H

#include <QWidget>
#include <QPixmap>

class Magnifier : public QWidget
{
    Q_OBJECT

public:
    Magnifier(QWidget *parent = 0);
    ~Magnifier();

protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

    void enterEvent(QEvent *event);

private:
    /*保存整个桌面*/
    QPixmap windowPixmap;
    /*保存要显示的画面，根据放大倍数，成比例的缩小大小*/
    QPixmap copyPixmap;
    /*保存鼠标在应用上点击的开始坐标，为了与移动时的当前坐标计算差值，从而知道要在桌面上移动多少距离*/
    QPoint windowMoveStart;
};

#endif // MAGNIFIER_H
