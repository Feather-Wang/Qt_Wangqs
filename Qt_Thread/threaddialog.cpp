#include "threaddialog.h"

#include <QtDebug>

#include <QPushButton>
#include <QCloseEvent>
#include <QVBoxLayout>

ThreadDialog::ThreadDialog(QWidget *parent) : QDialog(parent)
{
    threadA.setMessage("A");
    threadB.setMessage("B");

    threadAButton = new QPushButton(tr("Start A"));
    threadBButton = new QPushButton(tr("Start B"));
    quitButton = new QPushButton(tr("Quit"));
    quitButton->setDefault(true);

    connect(threadAButton, SIGNAL(clicked(bool)), this, SLOT(startOrStopThreadA()));
    connect(threadBButton, SIGNAL(clicked(bool)), this, SLOT(startOrStopThreadB()));
    connect(quitButton, SIGNAL(clicked(bool)), this, SLOT(close()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(threadAButton);
    layout->addWidget(threadBButton);
    layout->addWidget(quitButton);

    setLayout(layout);
}

void ThreadDialog::startOrStopThreadA()
{
    if( threadA.isRunning() )
    {
        threadA.stop();
        threadAButton->setText(tr("Start A"));
    }
    else
    {
        threadA.start();
        threadAButton->setText(tr("Stop A"));
    }
}

void ThreadDialog::startOrStopThreadB()
{
    if( threadB.isRunning() )
    {
        threadB.stop();
        threadBButton->setText(tr("Start B"));
    }
    else
    {
        threadB.start();
        threadBButton->setText(tr("Stop B"));
    }
}

void ThreadDialog::closeEvent(QCloseEvent *event)
{
    qDebug() << "closeEvent()";
    threadA.stop();
    threadB.stop();
    threadA.wait();
    threadB.wait();
    event->accept();
}
