#include "directoryviewer.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPushButton *insertButton = new QPushButton(QObject::tr("insert"));
    QPushButton *deleteButton = new QPushButton(QObject::tr("delete"));

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(insertButton);
    hboxLayout->addWidget(deleteButton);

    DirectoryViewer *viewer = new DirectoryViewer;
    viewer->sizeHint();

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(viewer);
    vboxLayout->addLayout(hboxLayout);

    QObject::connect(insertButton, SIGNAL(clicked(bool)), viewer, SLOT(createDirectory()));
    QObject::connect(deleteButton, SIGNAL(clicked(bool)), viewer, SLOT(removeDirectory()));

    QWidget w;
    w.setLayout(vboxLayout);
    w.show();

    return a.exec();
}
