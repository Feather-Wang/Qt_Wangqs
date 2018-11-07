#include "mainwindow.h"
#include "ui_mainwindow.h"


#include <QtGui>
#include <QMessageBox>
#include <QFileDialog>
#include <QTableWidgetSelectionRange>

#include "finddialog.h"
#include "usedesignerwindow.h"
#include "sortdialog.h"
#include "spreadsheet.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qDebug() << "MainWindow() 1";
    /*创建spreadshet部件，并将它设置为这个主窗口的中央窗口部件，中央窗口部件会占用主窗口的的中央区域部分*/
    spreadsheet = new Spreadsheet;
    setCentralWidget(spreadsheet);

    qDebug() << "MainWindow() 2";
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

    qDebug() << "MainWindow() 7";
    /*加载存储的设置*/
    readSettings();

    qDebug() << "MainWindow() 8";
    /*这里，将findDialog设置为空指针，在调用find()时将会创建该findDialog对象*/
    findDialog = 0;

    qDebug() << "MainWindow() 9";
    /*设置窗口的左上角的图标*/
    setWindowIcon(QIcon(":/images/icon.png"));
    setCurrentFile("");
    qDebug() << "MainWindow() 10";
}

MainWindow::~MainWindow()
{
    delete ui;
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
    newAction->setStatusTip(tr("Create a new spreadsheet file"));
    /*添加信号-槽关系*/
    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(newFile()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("Exit the application"));
    connect(exitAction, SIGNAL(triggered(bool)), this, SLOT(close()));

    openAction = new QAction(tr("&Open"), this);
    openAction->setIcon(QIcon(":/images/images/open.png"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("Open a spreadsheet file"));
    connect(openAction, SIGNAL(triggered(bool)), this, SLOT(open()));

    saveAction = new QAction(tr("&Save"), this);
    saveAction->setIcon(QIcon(":/images/images/save.png"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("Save a spreadsheet file"));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(save()));

    saveAsAction = new QAction(tr("&SaveAs"), this);
    saveAsAction->setIcon(QIcon(":/images/images/save.png"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("SaveAs a spreadsheet file"));
    connect(saveAsAction, SIGNAL(triggered(bool)), this, SLOT(saveAs()));

    cutAction = new QAction(tr("&Cut"), this);
    cutAction->setIcon(QIcon(":/images/images/cut.png"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("cut data"));
    connect(cutAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(cut()));

    copyAction = new QAction(tr("&Copy"), this);
    copyAction->setIcon(QIcon(":/images/images/copy.png"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("copy data"));
    connect(copyAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(copy()));

    pasteAction = new QAction(tr("&Paste"), this);
    pasteAction->setIcon(QIcon(":/images/images/paste.png"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("paste data"));
    connect(pasteAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(paste()));

    deleteAction = new QAction(tr("&Delete"), this);
    deleteAction->setIcon(QIcon(":/images/images/delete.png"));
    deleteAction->setShortcut(QKeySequence::Delete);
    deleteAction->setStatusTip(tr("delete data"));
    connect(deleteAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(del()));

    for(int i = 0; i < MaxRecentFiles; i++)
    {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered(bool)), this, SLOT(openRecentFile()));
    }

    sortAction = new QAction(tr("&Sort"), this);
    sortAction->setIcon(QIcon(":/images/images/paste.png"));
    sortAction->setStatusTip(tr("sort data"));
    connect(sortAction, SIGNAL(triggered(bool)), this, SLOT(sort()));

    findAction = new QAction(tr("&Find"), this);
    findAction->setIcon(QIcon(":/images/images/find.png"));
    findAction->setStatusTip(tr("find data"));
    connect(findAction, SIGNAL(triggered(bool)), this, SLOT(find()));

    useDesignerWindowAction = new QAction(tr(""), this);
    useDesignerWindowAction->setIcon(QIcon(":/images/images/cut.png"));
    useDesignerWindowAction->setStatusTip(tr("useDesignerWindow data"));
    connect(useDesignerWindowAction, SIGNAL(triggered(bool)), this, SLOT(useDesignerWindow()));

    selectAllAction = new QAction(tr("&All"), this);
    selectAllAction->setShortcut(QKeySequence::SelectAll);
    selectAllAction->setStatusTip(tr("Select all the cells in the spreadsheet"));
    connect(selectAllAction, SIGNAL(triggered(bool)), spreadsheet, SLOT(selectAll()));

    showGridAction = new QAction(tr("&Show Grid"), this);
    showGridAction->setCheckable(true);
    showGridAction->setChecked(spreadsheet->showGrid());
    showGridAction->setStatusTip(tr("Show or hide the spreadsheet's grid"));
    connect(showGridAction, SIGNAL(toggled(bool)), spreadsheet, SLOT(setShowGrid(bool)));

    aboutAction = new QAction(tr("About SpreadSheet"), this);
    aboutAction->setStatusTip(tr("Show SpreadSheet Infomation"));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));

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
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    /*插入一个分隔符(separator)，可以从视觉上把关系密切的这些项放在一起*/
    separatorAction = fileMenu->addSeparator();
    for(int i = 0; i < MaxRecentFiles; ++i)
        fileMenu->addAction(recentFileActions[i]);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    qDebug() << "createMenus() 2";
    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteAction);

    qDebug() << "createMenus() 3";
    selectSubMenu = editMenu->addMenu(tr("&Select"));
    //selectSubMenu->addAction(selectRowAction);
    //selectSubMenu->addAction(selectColumnAction);
    selectSubMenu->addAction(selectAllAction);

    qDebug() << "createMenus() 5";
    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    //toolsMenu->addAction(recalculateAction);
    toolsMenu->addAction(sortAction);
    toolsMenu->addAction(findAction);
    toolsMenu->addAction(useDesignerWindowAction);

    qDebug() << "createMenus() 6";
    optionsMenu = menuBar()->addMenu(tr("&Options"));
    optionsMenu->addAction(showGridAction);
    //optionsMenu->addAction(autoRecalcAction);

    qDebug() << "createMenus() 7";
    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
    qDebug() << "createMenus() 8";
}

void MainWindow::createContextMenu()
{
    /*创建上下文菜单*/
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);
    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::createToolBars()
{
    /*与创建菜单基本一样，区别是菜单使用QMainWindow::menuBar()->addMenu()添加菜单，工具栏使用QMainWindow::addToolBar()添加工具栏*/
    fileToolBar = addToolBar(tr("&File"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("&Edit"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addAction(deleteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(sortAction);
    editToolBar->addAction(findAction);
    editToolBar->addAction(useDesignerWindowAction);
}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel("W999");
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    /*为formulaLabel添加一个缩进格式*/
    formulaLabel->setIndent(3);

    /*QMainWindow::statusBar()函数返回一个指向状态栏的指针（在第一次调用statusBar()函数的时候会创建状态栏）*/
    /*在状态栏中添加了两个label，第一个label做指示器，第二个label做显示内容*/
    /*其中在添加第二个label的时候，指定了一个伸展因子“1”（默认为0，意味着不喜欢被伸展），作用是任何状态栏中任何多余的控件都分配给第二个label，当状态栏摆放这些窗口部件时，会尽量考虑由QWidget::sizeHint()提供的每一个窗口部件的理想大小，然后再对那些可伸展的任意窗口部件进行伸展以填满全部可用空间。*/
    /*一个窗口部件的理想大小，取决于这个窗口部件的内容以及改变内容时的变化大小。为了避免对使用了QWidget::sizeHint()的窗口部件连续不断地重定义大小，设置它的最小尺寸大小为它所能包含的最大字符数（“W999”）和一些空格的总大小，还把它的对其方式设置为Qt::AlignHCenter，以便可以在水平方向上居中对齐它的文本*/
    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

    connect(spreadsheet, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(updateStatusBar()));
    connect(spreadsheet, SIGNAL(modified()), this, SLOT(spreadsheetModified()));

    updateStatusBar();
}

void MainWindow::updateStatusBar()
{
    locationLabel->setText(spreadsheet->currentLocation());
    formulaLabel->setText(spreadsheet->currentFormula());
}

void MainWindow::spreadsheetModified()
{
    /*更新标题栏*/
    setWindowModified(true);
    updateStatusBar();
}

bool MainWindow::okToContinue()
{
    if(isWindowModified())
    {
        int r = QMessageBox::warning(this, tr("Spreadsheet"), tr("The document has been modified.\nDo you want to save your changes?"), QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if( QMessageBox::Yes == r )
        {
            return save();
        }
        else if( QMessageBox::Cancel == r )
        {
            return false;
        }
    }

    return true;
}

void MainWindow::newFile()
{
    if(okToContinue())
    {
        /*清空全部单元格和公式*/
        spreadsheet->clear();
        /*更新窗口的标题*/
        setCurrentFile("");
    }
}

void MainWindow::open()
{
    if( okToContinue() )
    {
        /*弹出一个文件选择框，返回值为文件名*/
        QString fileName = QFileDialog::getOpenFileName(this, tr("Open Spreadsheet"), ".", tr("Spreadsheet files (*.sp)"));

        if( !fileName.isEmpty() )
        {
            loadFile(fileName);
        }
    }
}

bool MainWindow::loadFile(const QString &fileName)
{
    /*读取文件，失败，则通过状态栏提示取消，显示时间2000毫秒*/
    if( !spreadsheet->readFile(fileName) )
    {
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }

    /*成功，则更新窗口的标题，并通过状态栏提示成功，显示时间2000毫秒*/
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
    return true;
}

bool MainWindow::save()
{
    if( curFile.isEmpty() )
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }
}

bool MainWindow::saveFile(const QString &fileName)
{
    if( !spreadsheet->writeFile(fileName) )
    {
        statusBar()->showMessage(tr("Saving canceled"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

bool MainWindow::saveAs()
{
    /*弹出一个文件对话框，用于从用户获取一个文件名，如果用户点击了cancel，则返回一个空串，返回false，这将会使这个结果向上传递给它的调用者*/
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Spreadsheet"), ".", tr("Spreadsheet files (*.sp)"));
    if( fileName.isEmpty() )
    {
        return false;
    }

    return saveFile(fileName);
}

/*当用户点击File->Exit或者单击窗口标题栏中的关闭按钮时，将会调用QWidge::close()槽。该槽会给这个窗口部件发射一个“close”信号。通过重新实现QWidget::closeEvent()函数，就可以中途截取对这个主窗口的关闭操作，并且可以确定到底是不是真的要关闭这个窗口*/
void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "MainWindow::closeEvent()";
    /*如果用户点击了确认，将会保存配置，否则，将会忽略这个关闭事件并且让这个窗口不受该操作的影响。*/
    if( okToContinue() )
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    /*每个QWidget都有一个windowModified属性，如果该窗口的文档存在没有保存的变化，则应当把它设置为true，否则应当将其设置为false*/
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if( !curFile.isEmpty() )
    {
        shownName = strippedName(curFile);
        /*将curFile从recentFiles移除*/
        recentFiles.removeAll(curFile);
        /*将curFile放入到recentFiles的第一项*/
        recentFiles.prepend(curFile);
        /*更新File菜单中的那些条目*/
        updateRecentFileActions();
    }

    /*在windows上，通过在文件名后加一个星号，表示这个文档还没有保存*/
    /*后面的arg()是用于替换前面的%1和%2的，第一个arg将会把参数shownName替换掉%1，第二个arg将会替换掉%2*/
    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Spreadsheet")));
}

/*移除文件名中的路径字符*/
QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);

    /*移除不存在的文件*/
    while( i.hasNext() )
    {
        if( !QFile::exists(i.next()) )
            i.remove();
    }

    for( int j = 0; j < MaxRecentFiles; ++j )
    {
        if( j < recentFiles.count() )
        {
            QString text = tr("&%1 %2").arg(j+1).arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
        {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

void MainWindow::openRecentFile()
{
    if( okToContinue() )
    {
        /*qobject_cast<T>()函数可在Qt的moc所生成的元信息基础上执行动态类型强制转换。
        它返回一个指向QObject子类的指针，或者是在该对象不能被转换成所需的那种类型时返回0。
        与标准C++的dynamic_case<T>()不同，Qt的qobject_cast<T>()可正确地跨越动态库边界。
        在这里，使用qobject_cast<T>()把一个QObject指针转换成QAction指针，如果这个转换是
        成功的（应当是这样的），就可以利用从动作的data项中所提取的文件全名来调用loadFile()函数。
        顺便值得一提的是，由于知道这个发射器是一个QAction，如果使用static_cast<T>()或者传统的C
        风格的数据类型强制转换代替原有的数据转换方式，这个程序应当仍然可以运行。

        在这里，通过QObject::sender()可以查出是哪个特有动作调用了这个槽。
        */
        QAction *action = qobject_cast<QAction *>(sender());
        if( action )
        {
            loadFile(action->data().toString());
        }
    }
}

void MainWindow::find()
{
    if( !findDialog )
    {
        /*本应该在MainWindow的构造函数中创建这个对话框，但是推迟对话框的创建过程将可以使程序的启动更加快速。
        还有，如果从来没有使用到这个对话框，那么它就绝不会被创建，这样可以既节省时间又节省内存。
        */
        findDialog = new FindDialog(this);
        connect(findDialog, SIGNAL(findNext(QString,Qt::CaseSensitivity)), spreadsheet, SLOT(findNext(QString,Qt::CaseSensitivity)));
        connect(findDialog, SIGNAL(findPrevious(QString,Qt::CaseSensitivity)), spreadsheet, SLOT(findPrevious(QString,Qt::CaseSensitivity)));
    }

    /*调用show(),raise(),activateWindow()来确保窗口位于其它窗口之上并且是可见的和激活的。
     * 只调用show()就足以让一个隐藏窗口变成可见的、位于最上方的并且是激活的，但是也有可能是在Find对话框
     * 窗口已经是可见额时候又再次调用了它，在这种情况下，show()调用可能什么也不做，那么就必须调用raise()
     * 和activteWindow()让窗口成为顶层和激活状态。
    */
    findDialog->show();
    findDialog->raise();
    findDialog->activateWindow();
}

void MainWindow::useDesignerWindow()
{
    UseDesignerWindow *dialog = new UseDesignerWindow(this);
    /*如果对话框被接收，函数exec()会返回一个true，否则会返回一个false*/
    if( dialog->exec() )
    {
        QString str = dialog->lineEdit->text().toUpper();
        spreadsheet->setCurrentCell(str.mid(1).toInt()-1, str[0].unicode()-'A');
    }
    delete dialog;
}

void MainWindow::sort()
{
    qDebug() << "MainWindow::sort()";
    SortDialog dialog(this);
    QTableWidgetSelectionRange range = spreadsheet->selectedRange();

    /*将那些可用于排序的列变量设置为选定的列*/
    dialog.setColumnRange('A' + range.leftColumn(), 'A' + range.rightColumn());

    qDebug() << "dialog.exec() before" << range.leftColumn() << ":" << range.rightColumn();
    if( dialog.exec() )
    {
        qDebug() << "dialog.exec() after";
        /*compare对象存储了主键、第二键、第三键，以及它们的排列顺序，这个对象会由Spreadsheet::sot()使用，用于两行的比较*/
        SpreadsheetCompare compare;
        /*keys数组存储了这些键的列号*/
        compare.keys[0] = dialog.primaryColumnCombo->currentIndex();
        compare.keys[1] = dialog.secondaryColumnCombo->currentIndex() - 1;
        compare.keys[2] = dialog.tertiaryColumnCombo->currentIndex() - 1;
        qDebug() << compare.keys[0] << ":" << compare.keys[1] << ":" << compare.keys[2];
        /*ascending数组中按bool格式存储了和每一个键相关的顺序，currentIndex()返回当前选定项的索引值，该值是一个从0开始的数，
         * 第二键和第三键，考虑到“None”项，所以从当前项减去1
        */
        compare.ascending[0] = (dialog.primaryOrderCombo->currentIndex() == 0);
        compare.ascending[1] = (dialog.secondaryOrderCombo->currentIndex() == 0);
        compare.ascending[2] = (dialog.tertiaryOrderCombo->currentIndex() == 0);
qDebug() << compare.ascending[0] << ":" << compare.ascending[1] << ":" << compare.ascending[2];
        spreadsheet->sort(compare);
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About Spreadsheet"), tr("<h2>Spreadsheet 1.1</h2>"
                                                         "<p>Copyright &copy; 2008 Software Inc."
                                                         "<p>Spreadsheet is a small application that "
                                                         "demonstrates QAction, QMainWindow, QMenuBar, QStatusBar, QTableWidget, QToolbar, and many other Qt classes."));
}

void MainWindow::writeSettings()
{
    /*QSettings，默认情况下，会存储应用程序中与特定平台相关的一些设置信息。
     * 在windows下，它使用的是系统注册表，在unix系统中，它会把设置信息存储在文本文档中，
     * 在Mac os中，它会使用Core Foundation Preferences的应用程序编程接口。
     * 构造函数的参数，说明了组织的名字和应用程序的名字，采用与平台相关的方式，可以利用这一信息
     * 查找这些设置所在的位置。
     * QSettings把设置信息存储为键值对的形式。
     * 键与文件系统的路径很相似，可以使用路径形式的语法（例如，findDialog/matchCase）来指定子健的值
     * 也可以使用beginGroup()和endGroup()的形式。
     * 值可以是一个int、bool、double、QString、QStringList或者是QVariant所支持的其它任意类型，
     * 包括哪些已经注册过的自定义类型。
    */
    QSettings settings("Software Inc.", "Spreadsheet");

    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", showGridAction->isChecked());
    settings.setValue("autoRecalc", autoRecalcAction->isChecked());
}

void MainWindow::readSettings()
{
    qDebug() << "MainWindow::readSettings() 1";
    QSettings settings("Software Inc.", "Spreadsheet");

    qDebug() << "MainWindow::readSettings() 2";
    restoreGeometry(settings.value("geometry").toByteArray());

    qDebug() << "MainWindow::readSettings() 3";
    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    qDebug() << "MainWindow::readSettings() 4";
    bool showGrid = settings.value("showGrid", true).toBool();
    showGridAction->setChecked(showGrid);

    qDebug() << "MainWindow::readSettings() 5";
    bool autoRecalc = settings.value("autoRecalc", true).toBool();

    qDebug() << "MainWindow::readSettings() 6";
    //autoRecalcAction->setChecked(autoRecalc);

}
