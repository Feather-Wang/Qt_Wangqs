#include "mystyle.h"

MyStyle::MyStyle()
{

}

void MyStyle::polish(QPalette &palette)
{
    palette.setBrush(QPalette::ButtonText, Qt::red);
}
