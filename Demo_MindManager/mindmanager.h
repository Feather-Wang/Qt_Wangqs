#ifndef MINDMANAGER_H
#define MINDMANAGER_H

#include <QMainWindow>

class QGraphicsView;
class QGraphicsScene;

class QAction;
class QToolBar;

#include "node.h"

class MindManager : public QMainWindow
{
    Q_OBJECT

public:
    MindManager(QWidget *parent = 0);
    ~MindManager();

private:
    QGraphicsView *view;
    QGraphicsScene *scene;

    QToolBar *operationToolBar;

    QAction *newChildNodeAction;
    QAction *delNodeAction;
    QAction *newBrotherNodeAction;


    void createActions();
    void createToolBar();
    void createContextMenu();

    void updateNode(Node *node);

private slots:
    void NewChildNode();
    void DelNode();
    void NewBrotherNode();
};

#endif // MINDMANAGER_H
