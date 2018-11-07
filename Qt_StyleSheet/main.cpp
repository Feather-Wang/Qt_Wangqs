#include <QApplication>
#include <QString>
#include <QDialog>
#include <QFile>
#include <QStyleFactory>

#include "candydialog.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setStyle(QStyleFactory::create("fusion"));

    QFile file(":/qss/candy.qss");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());

    CandyDialog dialog;
    dialog.show();

    return a.exec();
}
