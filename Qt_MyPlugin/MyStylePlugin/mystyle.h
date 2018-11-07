#ifndef MYSTYLE_H
#define MYSTYLE_H

#include <QProxyStyle>

class MyStyle : public QProxyStyle
{
public:
    MyStyle();

    void polish(QPalette &palette);
};

#endif // MYSTYLE_H
