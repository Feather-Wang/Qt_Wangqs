#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QPushButton>
#include <QLabel>

#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();
    void updateStatusBar();

private slots:
    void newFile();
    void openFile();
    void aboutApp();
    void openRecentFile();

private:
    QAction *newAction;
    QAction *openAction;
    QAction *recentFileActions[5];
    QAction *aboutAction;
    QAction *aboutQtAction;

    QMenu *fileMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *helpToolBar;

    QLabel *statusBarLabel;
    QLabel *formulaLabel;

    QPushButton *center_widget;

    const int MaxRecentFiles = 5;
};

#endif // MAINWINDOW_H
