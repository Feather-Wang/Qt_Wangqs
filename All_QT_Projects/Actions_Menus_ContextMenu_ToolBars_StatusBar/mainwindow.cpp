#include "mainwindow.h"

#include <QDebug>

#include <QMessageBox>

/*qApp需要ga该头文件*/
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    center_widget = new QPushButton(tr("center_widget"));
    center_widget->setFixedHeight(100);
    setCentralWidget(center_widget);

    /*完成菜单栏*/
    createActions();
    qDebug() << "MainWindow() 3";
    createMenus();
    qDebug() << "MainWindow() 4";
    createContextMenu();
    qDebug() << "MainWindow() 5";
    createToolBars();
    qDebug() << "MainWindow() 6";
    createStatusBar();

    setWindowIcon(QIcon(":/images/icon.png"));
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    /*创建一个new的动作对象，并且设置快捷键Alt+N，并且使用this作为父对象（父窗口）*/
    newAction = new QAction(tr("&New"), this);
    /*设置图标*/
    newAction->setIcon(QIcon(":/images/images/new.png"));
    /*设置一个加速键New*/
    newAction->setShortcut(QKeySequence::New);
    /*设置提示信息*/
    newAction->setStatusTip(tr("Create a new App file"));
    /*添加信号-槽关系*/
    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a App file"));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(openFile()));

    for(int i = 0; i < MaxRecentFiles; i++)
    {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(true);
        recentFileActions[i]->setText(QString::number(i));
        connect(recentFileActions[i], SIGNAL(triggered(bool)), this, SLOT(openRecentFile()));
    }

    aboutAction = new QAction(tr("About App"), this);
    aboutAction->setStatusTip(tr("Show App Infomation"));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(aboutApp()));

    aboutQtAction = new QAction(tr("About &Qt"), this);
    aboutQtAction->setStatusTip(tr("Show the Qt library's about box"));
    connect(aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    qDebug() << "createMenus() 1";
    /*在Qt中，菜单都是QMenu的实例，QMainWindow::menuBar()函数返回一个指向QMenuBar的指针（这个QMenuBar对象，在第一次调用menuBar()函数的时候就创建出来，通过QMenuBar对象的addMenu()函数，可以用给定的文本创建衣蛾QMenu窗口部件，并将它添加到菜单栏中*/
    fileMenu = menuBar()->addMenu(tr("&File"));
    /*菜单创建好后，就将属于其下的动作，通过addAction添加进去，添加的顺序和显示的顺序是一致的*/
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    /*插入一个分隔符(separator)，可以从视觉上把关系密切的这些项放在一起*/
    fileMenu->addSeparator();
    for(int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);

    qDebug() << "createMenus() 2";
    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
    qDebug() << "createMenus() 3";
}

void MainWindow::createContextMenu()
{
    /*创建上下文菜单*/
    center_widget->addAction(newAction);
    center_widget->addAction(openAction);
    center_widget->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
    /*与创建菜单基本一样，区别是菜单使用QMainWindow::menuBar()->addMenu()添加菜单，工具栏使用QMainWindow::addToolBar()添加工具栏*/
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addSeparator();

    helpToolBar = addToolBar(tr("&About"));
    helpToolBar->addAction(aboutAction);
    helpToolBar->addAction(aboutQtAction);
}

void MainWindow::createStatusBar()
{
    statusBarLabel = new QLabel("W999");
    statusBarLabel->setAlignment(Qt::AlignHCenter);
    statusBarLabel->setMinimumSize(statusBarLabel->sizeHint());

    formulaLabel = new QLabel;
    /*为formulaLabel添加一个缩进格式*/
    formulaLabel->setIndent(3);

    /*QMainWindow::statusBar()函数返回一个指向状态栏的指针（在第一次调用statusBar()函数的时候会创建状态栏）*/
    /*在状态栏中添加了两个label，第一个label做指示器，第二个label做显示内容*/
    /*其中在添加第二个label的时候，指定了一个伸展因子“1”（默认为0，意味着不喜欢被伸展），作用是任何状态栏中任何多余的控件都分配给第二个label，当状态栏摆放这些窗口部件时，会尽量考虑由QWidget::sizeHint()提供的每一个窗口部件的理想大小，然后再对那些可伸展的任意窗口部件进行伸展以填满全部可用空间。*/
    /*一个窗口部件的理想大小，取决于这个窗口部件的内容以及改变内容时的变化大小。为了避免对使用了QWidget::sizeHint()的窗口部件连续不断地重定义大小，设置它的最小尺寸大小为它所能包含的最大字符数（“W999”）和一些空格的总大小，还把它的对其方式设置为Qt::AlignHCenter，以便可以在水平方向上居中对齐它的文本*/
    statusBar()->addWidget(statusBarLabel);
    statusBar()->addWidget(formulaLabel, 1);

//    connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(updateStatusBar()));
//    connect(spreadsheet, SIGNAL(modified()), this, SLOT(spreadsheetModified()));

    updateStatusBar();
}

void MainWindow::updateStatusBar()
{
//    locationLabel->setText(spreadsheet->currentLocation());
//    formulaLabel->setText(spreadsheet->currentFormula());
}


void MainWindow::newFile()
{
        QMessageBox::about(this, tr("newFile title"), tr("<h2>newFile</h2>"));
}

void MainWindow::openFile()
{
    QMessageBox::about(this, tr("openFile title"), tr("<h2>openFile</h2>"));
}

void MainWindow::aboutApp()
{
    QMessageBox::about(this, tr("About App"), tr("<h2>App 1.1</h2>"
                                                         "<p>Copyright &copy; 2008 Software Inc."
                                                         "<p>App is a small application that "
                                                         "demonstrates QAction, QMainWindow, QMenuBar, QStatusBar, QTableWidget, QToolbar, and many other Qt classes."));
}

void MainWindow::openRecentFile()
{
    QMessageBox::about(this, tr("openRecentFile title"), tr("<h2>openRecentFile</h2>"));
}
