#include "printwindow.h"
#include <QPrintDialog>
#include <QPrinter>

void PrintWindow()
{}

void PrintWindow::printFlowerGuide(const QStringList &entries)
{
    QString html;
    
    foreach (QString entry, entries) {
        QStringList fields = entry.split(": ");
        QString title = fields[0];
        QString body = fields[1];
        html += "<table width=\"100%\" border=1 cellspacing=0>\n"
                "<tr><td bgcolor=\"lightgray\"><font size=\"+1\">"
                "<b><i>" + title + "</i></b></font>\n<tr><td>" + body
                + "\n</table>\n<br>\n";
    }
    printHtml(html);
}

void PrintWindow::printHtml(const QString &html)
{
    QPrinter printer(QPrinter::HighResolution);
    qDebug()<<printer.isValid()<<printer.printerName();
    QPrintDialog dialog(&printer);

    if (dialog.exec()) {
        qDebug()<<printer.isValid()<<printer.printerName();
        QPainter painter(&printer);
        QRect rect = painter.viewport();
        QSize size(100,200);
        size.scale(rect.size(), Qt::KeepAspectRatio);
        painter.setViewport(rect.x(), rect.y(), size.width(), size.height());
        //painter.setWindow(new QRect(100, 200));

        //生成一个5页的pdf文档
//        {
//            QList<QPixmap> pPixmapList;
//            for(int i=0; i<5;i++)
//            {
//                pPixmapList.append(QPixmap(*imageLabel->pixmap()));
//            }
//            for(int i=0;i<5;i++)
//            {
//                painter.drawPixmap(0, 0, pPixmapList.at(i));
//                if(i!=4)
//                    printer.newPage();
//            }
//        }
    }

}
