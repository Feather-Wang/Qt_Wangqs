#ifndef USESIMPLEWINDOW_H
#define USESIMPLEWINDOW_H

#include <QWidget>
#include "interface.h"
#include <QLineEdit>

class UseSimpleWindow : public QWidget
{
    Q_OBJECT
public:
    explicit UseSimpleWindow(QWidget *parent = 0);

signals:

public slots:
    void output();

private:
    bool loadPlugin();

    InterFace *interface;
    QLineEdit *in;
    QLineEdit *out;
};

#endif // USESIMPLEWINDOW_H
