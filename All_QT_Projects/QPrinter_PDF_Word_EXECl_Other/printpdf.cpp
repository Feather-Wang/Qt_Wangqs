#include "printpdf.h"



PrintPDF::PrintPDF(QWidget *parent)
    : QWidget(parent)
{
    printFile(tr("wangqingsong"));
    createPdf();
}

PrintPDF::~PrintPDF()
{

}


bool PrintPDF::printFile(const QString & filePath)
{
    QPrinter printer;
    QPrintDialog *dialog = new QPrintDialog(&printer);
//        if(editor->textCursor().hasSelection())
//            dialog->addEnabledOption(QabstractPrintDialog::PrintSelection);
    if (dialog->exec() != QDialog::Accepted)
        return true;
}

void PrintPDF::doPrint()
{
    // 创建打印机对象
    QPrinter printer;
    // 创建打印对话框
    QString printerName = printer.printerName();
    if( printerName.size() == 0)
        return;
    QPrintDialog dlg(&printer, this);
    //如果编辑器中有选中区域，则打印选中区域
    if (text_edit.textCursor().hasSelection())
        dlg.addEnabledOption(QAbstractPrintDialog::PrintSelection);
    // 如果在对话框中按下了打印按钮，则执行打印操作
    if (dlg.exec() == QDialog::Accepted)
    {
        text_edit.print(&printer);
        // print the existing document by absoult path
        //  printFile("D:/myRSM.doc");
    }
}
// 打印预览
void PrintPDF::doPrintPreview()
{
    QPrinter printer;
    // 创建打印预览对话框
    QPrintPreviewDialog preview(&printer, this);
    // 当要生成预览页面时，发射paintRequested()信号
    connect(&preview, SIGNAL(paintRequested(QPrinter*)),
            this,SLOT(printPreview(QPrinter*)));
    preview.exec();
}
void PrintPDF::printPreview(QPrinter *printer)
{
    text_edit.print(printer);
}
#include <QTextEdit>
// 生成PDF文件
void PrintPDF::createPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("导出PDF文件"), QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        // 如果文件后缀为空，则默认使用.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer;
        // 指定输出格式为pdf
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        text_edit.setText(tr("wangqingsong"));
        text_edit.print(&printer);
    }
}

// 页面设置
void PrintPDF::setUpPage()
{
    QPrinter printer;
    QPageSetupDialog pageSetUpdlg(&printer, this);
    if (pageSetUpdlg.exec() == QDialog::Accepted)
    {
        printer.setOrientation(QPrinter::Landscape);
    }
    else
    {
        printer.setOrientation(QPrinter::Portrait);
    }
}
