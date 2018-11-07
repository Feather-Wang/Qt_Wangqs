#include "animation.h"

#include <QPropertyAnimation>
#include <QPushButton>

#include <QtDebug>

Animation::Animation(QWidget *parent) :
    QWidget(parent)
{

}

Animation::~Animation()
{
}

/*
当鼠标在应用上点击时，启动动画
*/
void Animation::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "mousePressEvent";

    QPushButton *button = new QPushButton("animation button", this);
    button->show();

    /*定义QPropertyAnimation对象，将button设置为动画对象，动画属性为button的geometry*/
    QPropertyAnimation *animation = new QPropertyAnimation(button, "geometry");

    /*设置动画的时间*/
    animation->setDuration(10000);
    /*
    设置button的geometry的开始属性和结束属性，以及中间的几个状态的属性，中间的几个状态是从0-1选取的，开始点是0，借宿点是1，中间点就是0.x。
    这里分别在0.4和0.8设置了button的属性，而animation会这几个点之间进行合理的动画变化效果。
    */
    animation->setStartValue(QRect(0, 0, 0, 0));
    animation->setKeyValueAt(0.4, QRect(20, 250, 20, 30));
    animation->setKeyValueAt(0.8, QRect(100, 250, 20, 30));
    animation->setEndValue(QRect(250, 250, button->width(), button->height()));

    animation->start();
}
