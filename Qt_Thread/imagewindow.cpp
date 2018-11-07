#include "imagewindow.h"

#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QApplication>
#include <QImageReader>

ImageWindow::ImageWindow(QWidget *parent)
    :QMainWindow(parent)
{
    /*将QLabel设置成窗口的中央窗口部件，用于加载显示图片*/
    imageLabel = new QLabel;
    imageLabel->setBackgroundRole(QPalette::Dark);
    imageLabel->setAutoFillBackground(true);
    imageLabel->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setCentralWidget(imageLabel);

    /*设置两个按键，到窗口的工具栏上，当用户点击对应的按钮后，将会添加对应的处理事件，到线程的处理队列中*/
    flipHorizontallyAction = new QAction(tr("Flip Horizontally"), this);
    connect(flipHorizontallyAction, SIGNAL(triggered()), this, SLOT(flipHorizontally()));
    flipVerticallyAction = new QAction(tr("Flip &Vertically"), this);
    connect(flipVerticallyAction, SIGNAL(triggered()), this, SLOT(flipVertically()));
    addToolBar(tr("tool"))->addAction(flipHorizontallyAction);
    addToolBar(tr("tool"))->addAction(flipVerticallyAction);

    /*加载图片，并在状态栏上显示Ready*/
    loadFile(":/images/moves.jpg");
    statusBar()->showMessage(tr("Ready"), 2000);

    /*设置后台处理线程和窗口部件的信号-槽连接*/
    /*当开始处理时，线程将会发送一个ThreadProcessStart信号，本窗口部件接收到后，将会把线程发送过来的字符串显示到状态栏上*/
    connect(&thread, SIGNAL(ThreadProcessStart(const QString &)), statusBar(), SLOT(showMessage(const QString &)));
    /*当线程处理完数据后，将会发送一个ThreadProcessDone信号，本窗口部件接收到后，将会调用ShowImage()槽，重新刷新图片显示*/
    connect(&thread, SIGNAL(ThreadProcessDone()), this, SLOT(ShowImage()));
}

void ImageWindow::flipHorizontally()
{
    thread.addTransaction(new Transaction(Qt::Horizontal));
}

void ImageWindow::flipVertically()
{
    thread.addTransaction(new Transaction(Qt::Vertical));
}

void ImageWindow::ShowImage()
{
    imageLabel->setPixmap(QPixmap::fromImage(thread.image()));
    statusBar()->showMessage(tr("Ready"), 2000);
}

void ImageWindow::loadFile(const QString &fileName)
{
    QImage newImage;

    /*修改鼠标光标为等待状态，然后加载图片，加载完成后，将光标恢复原状*/
    QApplication::setOverrideCursor(Qt::WaitCursor);
    bool loaded = newImage.load(fileName);
    QApplication::restoreOverrideCursor();

    if (loaded)
    {
        /*如果加载成功，则将newImage设置到次线程中*/
        thread.setImage(newImage);
        imageLabel->setPixmap(QPixmap::fromImage(newImage));
        statusBar()->showMessage(tr("File loaded"), 2000);
    } else {
        QMessageBox::warning(this, tr("Image Pro"), tr("Error when loading image."));
        statusBar()->showMessage(tr("Loading canceled"), 2000);
    }
}
