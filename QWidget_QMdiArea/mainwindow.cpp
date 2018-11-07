#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMdiArea>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mdiArea = new QMdiArea;
    setCentralWidget(mdiArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}
