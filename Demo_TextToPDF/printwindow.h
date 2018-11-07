#ifndef PRINTWINDOW_H
#define PRINTWINDOW_H

#include <QtGui>

class PrintWindow
{
public:
    PrintWindow();

    void printHtml(const QString &html);
    void printFlowerGuide(const QStringList &entries);
};

#endif // PRINTWINDOW_H
