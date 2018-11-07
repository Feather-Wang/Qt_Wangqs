#ifndef ANIMATION_H
#define ANIMATION_H

#include <QWidget>

class QMouseEvent;

class Animation : public QWidget
{
    Q_OBJECT

public:
    explicit Animation(QWidget *parent = 0);
    ~Animation();

protected:
    void mousePressEvent(QMouseEvent *event);

};

#endif // ANIMATION_H
