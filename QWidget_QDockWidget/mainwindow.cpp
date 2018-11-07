#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPushButton>
#include <QTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    button = new QPushButton("show");
    setCentralWidget(button);
}

MainWindow::~MainWindow()
{
    delete ui;
}
