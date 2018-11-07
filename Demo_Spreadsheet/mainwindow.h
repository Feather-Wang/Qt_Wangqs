        #ifndef MAINWINDOW_H
    #define MAINWINDOW_H

    #include <QMainWindow>

    class QAction;
    class QLabel;
    class FindDialog;
    class Spreadsheet;

    namespace Ui {
    class MainWindow;
    }

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

    protected:
        /*该函数是QWidget类中的一个虚函数，当窗体关闭时，将会自动调用这个函数，在这里重新实现它以便在用户要关闭窗体时，进行第二次确认*/
        void closeEvent(QCloseEvent *event);

    private slots:
        void newFile();
        void open();
        bool save();
        bool saveAs();
        void find();
        void useDesignerWindow();
        void sort();
        void about();
        void openRecentFile();
        void updateStatusBar();
        void spreadsheetModified();

    private:
        void createActions();
        void createMenus();
        void createContextMenu();
        void createToolBars();
        void createStatusBar();
        void readSettings();
        void writeSettings();
        bool okToContinue();
        bool loadFile(const QString &fileName);
        bool saveFile(const QString &fileName);
        void setCurrentFile(const QString &fileName);
        void updateRecentFileActions();
        QString strippedName(const QString &fullFileName);

        Spreadsheet *spreadsheet;
        FindDialog *findDialog;
        QLabel *locationLabel;
        QLabel *formulaLabel;
        QStringList recentFiles;
        QString curFile;


        /*菜单栏*/
        QMenu *fileMenu;
        QMenu *editMenu;
        QMenu *selectSubMenu;
        QMenu *toolsMenu;
        QMenu *optionsMenu;
        QMenu *helpMenu;

        /*工具栏*/
        QToolBar *fileToolBar;
        QToolBar *editToolBar;

        /*动作*/
        enum { MaxRecentFiles = 5 };

        QAction *recentFileActions[MaxRecentFiles];
        QAction *separatorAction;

        QAction *newAction;
        QAction *exitAction;
        QAction *openAction;
        QAction *saveAction;
        QAction *saveAsAction;

        QAction *cutAction;
        QAction *copyAction;
        QAction *pasteAction;
        QAction *deleteAction;

        QAction *showGridAction;
        QAction *autoRecalcAction;

        QAction *selectAllAction;
        QAction *selectRowAction;
        QAction *selectColumnAction;

        QAction *sortAction;
        QAction *findAction;
        QAction *useDesignerWindowAction;

        QAction *recalculateAction;

        QAction *aboutAction;
        QAction *aboutQtAction;
    };

    #endif // MAINWINDOW_H
