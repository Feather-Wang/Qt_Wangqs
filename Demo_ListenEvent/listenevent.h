#ifndef LISTENEVENT_H
#define LISTENEVENT_H

#include <QWidget>

class QLineEdit;

class ListenEvent : public QWidget
{
    Q_OBJECT
public:
    explicit ListenEvent(QWidget *parent = 0);

private:
    QLineEdit *line01;
    QLineEdit *line02;
    QLineEdit *line03;

protected:
    bool eventFilter(QObject *watched, QEvent *event);

signals:

public slots:
};

#endif // LISTENEVENT_H
