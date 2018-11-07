#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->show();

    qDebug() << "splash->show() finish";

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::white);
    qDebug() << "splash->showMessage() finish";

    MainWindow w;
    w.show();

    splash->finish( &w );
    delete splash;

    return a.exec();
}
