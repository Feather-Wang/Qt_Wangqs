#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    button1 = new QPushButton(tr("button1"));
    button2 = new QPushButton(tr("button2"));
    button3 = new QPushButton(tr("button3"));

    button4 = new QPushButton(tr("button4"));
    button5 = new QPushButton(tr("button5"));

    QHBoxLayout *hbox_layout1 = new QHBoxLayout;
    hbox_layout1->addWidget(button1);
    hbox_layout1->addWidget(button2);
    hbox_layout1->addWidget(button3);

    QHBoxLayout *hbox_layout2 = new QHBoxLayout;
    hbox_layout1->addWidget(button4);
    hbox_layout1->addWidget(button5);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addLayout(hbox_layout1);
    layout->addLayout(hbox_layout2);

    setLayout(layout);

    setCentralWidget(button1);
}

MainWindow::~MainWindow()
{

}
