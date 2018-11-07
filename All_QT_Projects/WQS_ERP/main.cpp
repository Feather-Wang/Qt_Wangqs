#include "wqs_erp.h"
#include <QApplication>

#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    wqs_erp erp_show;
    erp_show.show();

    return a.exec();
}
