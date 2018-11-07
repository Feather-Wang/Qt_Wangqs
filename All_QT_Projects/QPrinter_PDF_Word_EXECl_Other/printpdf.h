#ifndef PRINTPDF_H
#define PRINTPDF_H

#include <QWidget>

#include <QTextEdit>
#include <QFileDialog>

#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QAbstractPrintDialog>
#include <QPageSetupDialog>

class PrintPDF : public QWidget
{
    Q_OBJECT

public:
    PrintPDF(QWidget *parent = 0);
    ~PrintPDF();

    bool printFile(const QString & filePath);

private slots:
    void doPrint();
    void doPrintPreview();
    void printPreview(QPrinter *printer);
    void createPdf();
    void setUpPage();

private:
    QTextEdit text_edit;
};

#endif // PRINTPDF_H
