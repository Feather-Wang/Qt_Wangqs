#include <QApplication>

#include "iconeditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    IconEditor *iconEditor = new IconEditor;
    iconEditor->show();

    return a.exec();
}
