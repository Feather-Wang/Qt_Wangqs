#include "usesimplewindow.h"

#include <QVBoxLayout>
#include <QtDebug>
#include <QDir>
#include <QPluginLoader>
#include <QApplication>


UseSimpleWindow::UseSimpleWindow(QWidget *parent) : QWidget(parent)
{
    in = new QLineEdit;
    out = new QLineEdit;

    connect(in, SIGNAL(editingFinished()), this, SLOT(output()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(in);
    layout->addWidget(out);

    setLayout(layout);

    if( !loadPlugin() )
    {
        qDebug() << "loadPlugin() error";
    }
}

void UseSimpleWindow::output()
{
    QString text = interface->echo(in->text());
    out->setText(text);
}

bool UseSimpleWindow::loadPlugin()
{
    QDir pluginsDir(qApp->applicationDirPath());

    pluginsDir.cd("simple");
    foreach (QString fileName, pluginsDir.entryList(QDir::Files))
    {
        qDebug() << "foreach --> fileName = " << pluginsDir.absoluteFilePath(fileName);

        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        QObject *plugin = pluginLoader.instance();
        if (plugin)
        {
            qDebug() << "a";
            interface = qobject_cast<InterFace *>(plugin);
            if( interface )
                return true;
            qDebug() << "error " << pluginLoader.errorString();
        }
    }

    return false;
}
