#include "printpdf.h"
#include "test_doc.h"

#include <QApplication>

#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    PrintPDF w;
//    w.show();

    qDebug() << "test_doc doc;";
    test_doc doc;

    return a.exec();
}
