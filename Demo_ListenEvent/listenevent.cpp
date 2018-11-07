#include "listenevent.h"

#include <QtGui>
#include <QLineEdit>
#include <QVBoxLayout>

ListenEvent::ListenEvent(QWidget *parent) : QWidget(parent)
{
    line01 = new QLineEdit("line 01");
    line02 = new QLineEdit("line 02");
    line03 = new QLineEdit("line 03");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(line01);
    layout->addWidget(line02);
    layout->addWidget(line03);

    setLayout(layout);

    line01->installEventFilter(this);
    line02->installEventFilter(this);
    line03->installEventFilter(this);
}

/*
事件过滤器
*/
bool ListenEvent::eventFilter(QObject *watched, QEvent *event)
{
    /*当有事件产生时，根据watched判断是哪个控件的事件*/
    if( watched == line01 ||
            watched == line02 ||
            watched == line03 )
    {
        if( event->type() == QEvent::KeyPress )
        {
            /*如果按键是空格，则将焦点移动到下一个控件*/
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if( keyEvent->key() == Qt::Key_Space )
            {
                focusNextChild();
                return true;
            }
        }
    }

    return QWidget::eventFilter(watched, event);
}
