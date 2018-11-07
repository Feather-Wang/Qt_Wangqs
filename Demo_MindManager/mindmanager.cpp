#include "mindmanager.h"

#include <QtGui>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <QAction>
#include <QToolBar>
#include <QMenu>

#include "node.h"

MindManager::MindManager(QWidget *parent)
    : QMainWindow(parent)
{
    createActions();
    createToolBar();
    createContextMenu();

    scene = new QGraphicsScene(0, 0, 600, 500);

    view = new QGraphicsView;
    view->setScene(scene);
    view->setDragMode(QGraphicsView::RubberBandDrag);
    view->setRenderHints(QPainter::Antialiasing
                         | QPainter::TextAntialiasing);
    view->setContextMenuPolicy(Qt::ActionsContextMenu);
    setCentralWidget(view);
}

MindManager::~MindManager()
{

}

/*添加动作对象，并设置相应的信号-槽映射关系*/
void MindManager::createActions()
{
    newChildNodeAction = new QAction(tr("NewChildNode"), this);
    newChildNodeAction->setShortcut(QKeySequence::New);
    newChildNodeAction->setStatusTip(tr("Create a New Child Node"));
    newChildNodeAction->setToolTip(tr("Create a New Child Node"));
    connect(newChildNodeAction, SIGNAL(triggered(bool)), this, SLOT(NewChildNode()));

    delNodeAction = new QAction(tr("DelNode"), this);
    delNodeAction->setShortcut(QKeySequence::Delete);
    delNodeAction->setStatusTip(tr("Delete a Node"));
    delNodeAction->setToolTip(tr("Delete a Node"));
    connect(delNodeAction, SIGNAL(triggered(bool)), this, SLOT(DelNode()));

    newBrotherNodeAction = new QAction(tr("NewBrotherNode"), this);
    newBrotherNodeAction->setShortcut(QKeySequence::New);
    newBrotherNodeAction->setStatusTip(tr("Create a New Brother Node"));
    newBrotherNodeAction->setToolTip(tr("Create a New Brother Node"));
    connect(newBrotherNodeAction, SIGNAL(triggered(bool)), this, SLOT(NewBrotherNode()));
}

/*将相关的动作对象，添加到工具栏中*/
void MindManager::createToolBar()
{
    operationToolBar = addToolBar(tr("Operation"));
    operationToolBar->addAction(newChildNodeAction);
    operationToolBar->addAction(delNodeAction);
    operationToolBar->addAction(newBrotherNodeAction);
}

/*将相关的动作对象，添加到右键菜单中*/
void MindManager::createContextMenu()
{
    addAction(newChildNodeAction);
    addAction(delNodeAction);
    addAction(newBrotherNodeAction);

    setContextMenuPolicy(Qt::ActionsContextMenu);
}

/*槽，对应于NewChildNodeAction动作对象，为当前Node创建一个子Node*/
void MindManager::NewChildNode()
{
    qDebug("NewChildNode()\n");
    Node *node = new Node;
    node->setText(tr("node"));
    updateNode(node);
}

/*槽，对应于DelNode动作对象，用于删除选中的Node*/
void MindManager::DelNode()
{
    qDebug("DelNode()\n");
}

/*槽，对应于NewBrotherAction动作对象，为当前Node创建一个兄弟Node，放在当前Node的下方*/
void MindManager::NewBrotherNode()
{
    qDebug("NewBrotherNode()\n");
}

void MindManager::updateNode(Node *node)
{
    node->setPos(QPoint(width()/2, height()/2));
    scene->addItem(node);

    /*清除当前的选中操作，并且将新添加的节点选中*/
    scene->clearSelection();
    node->setSelected(true);
}
