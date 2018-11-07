#include "personlist.h"
#include <QApplication>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QPushButton *insertButton = new QPushButton(QObject::tr("insert"));
    QPushButton *deleteButton = new QPushButton(QObject::tr("delete"));

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(insertButton);
    hboxLayout->addWidget(deleteButton);

    PersonList *personList = new PersonList;

    QVBoxLayout *vboxLayout = new QVBoxLayout;
    vboxLayout->addWidget(personList);
    vboxLayout->addLayout(hboxLayout);

    QObject::connect(insertButton, SIGNAL(clicked(bool)), personList, SLOT(insert()));
    QObject::connect(deleteButton, SIGNAL(clicked(bool)), personList, SLOT(del()));

    QWidget w;
    w.setLayout(vboxLayout);
    w.show();

    return a.exec();
}
