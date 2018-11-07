#include "mainwindow.h"

#include <QtGui>
#include <QTextEdit>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /*将textEdit设置为中心窗口*/
    textEdit = new QTextEdit;
    setCentralWidget(textEdit);

    /*textEdit，默认情况下，是可以接受来自其它应用程序文本的拖动，并且如果用户在它上面放下一个文本，它将会把这个文件的名称插入到文本中*/
    /*关闭textEdit的放下操作，开启当前窗口部件的放下操作*/
    textEdit->setAcceptDrops(false);
    setAcceptDrops(true);

    setWindowTitle(tr("Text Editor"));
}

MainWindow::~MainWindow()
{

}

/*拖放操作中的拖动事件，当用户把一个对象拖动到这个窗口部件上时，就会调用dragEnterEvent()。
如果对这个事件调用acceptProposedAction()，就表名用户可以在这个窗口部件上拖放对象。
默认情况下，窗口部件是不接受拖动的，Qt会自动改变光标来向用户说明这个窗口部件是不是有效的放下点*/
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug("dragEnterEvent()\n");
    /*这里，我们限定了拖动对象的类型，只能是文件*/
    if( event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

/*
拖动操作中的放下事件，当用户把一个对象拖动到这个窗口部件，然后放下时，放下操作会触发这个事件。
拖动对象，可以是一个，也可以是多个，通过event->mimeData()->urls()可以获取所有的拖动对象的URL
*/
void MainWindow::dropEvent(QDropEvent *event)
{
    qDebug("dropEvent()\n");
    QList<QUrl> urls = event->mimeData()->urls();
    if( urls.isEmpty() )
        return;

    QString fileName = urls.first().toLocalFile();
    if( fileName.isEmpty() )
        return;

    if( readFile(fileName) )
        setWindowTitle(tr("%1 - %2").arg(fileName).arg(tr("Drag File")));
}

bool MainWindow::readFile(const QString &fileName)
{
    textEdit->setText(fileName);
    return true;
}

void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{
    //qDebug("dragMoveEvent()\n");
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *event)
{
    qDebug("dragLeaveEvent()\n");
}
