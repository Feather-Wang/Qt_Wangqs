#ifndef DIRECTORYVIEWER_H
#define DIRECTORYVIEWER_H

#include <QDialog>

class QDirModel;
class QTreeView;

class DirectoryViewer : public QDialog
{
    Q_OBJECT

public:
    DirectoryViewer(QWidget *parent = 0);
    ~DirectoryViewer();

public slots:
    void createDirectory();
    void removeDirectory();

private:
    QDirModel *model;
    QTreeView *treeView;
};

#endif // DIRECTORYVIEWER_H
