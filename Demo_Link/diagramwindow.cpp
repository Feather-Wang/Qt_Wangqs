        #include <QtGui>

    #include "diagramwindow.h"
    #include "link.h"
    #include "node.h"
    #include "propertiesdialog.h"
    #include <QGraphicsScene>
    #include <QGraphicsView>
    #include <QColorDialog>
    #include <QAction>
    #include <QMenu>
    #include <QMenuBar>
    #include <QToolBar>

    DiagramWindow::DiagramWindow()
    {
        scene = new QGraphicsScene(0, 0, 600, 500);

        view = new QGraphicsView;
        view->setScene(scene);
        view->setDragMode(QGraphicsView::RubberBandDrag);
        view->setRenderHints(QPainter::Antialiasing
                             | QPainter::TextAntialiasing);
        view->setContextMenuPolicy(Qt::ActionsContextMenu);
        setCentralWidget(view);

        minZ = 0;
        maxZ = 0;
        seqNumber = 0;

        createActions();
        createMenus();
        createToolBars();

        connect(scene, SIGNAL(selectionChanged()),
                this, SLOT(updateActions()));

        setWindowTitle(tr("Diagram"));
        updateActions();
    }

    /*当用户添加了一个新的节点时，就可以创建一个新的Node类的实例，并赋予它默认的文字，
    然后把节点传给setupNode()来定位和选取它*/
    void DiagramWindow::addNode()
    {
        Node *node = new Node;
        node->setText(tr("Node %1").arg(seqNumber + 1));
        setupNode(node);
    }

    /*
    添加一个link
    */
    void DiagramWindow::addLink()
    {
        NodePair nodes = selectedNodePair();
        if (nodes == NodePair())
            return;

        Link *link = new Link(nodes.first, nodes.second);
        scene->addItem(link);
    }

    /*删除选中的项，可以是节点、link*/
    void DiagramWindow::del()
    {
        QList<QGraphicsItem *> items = scene->selectedItems();
        QMutableListIterator<QGraphicsItem *> i(items);
        while (i.hasNext()) {
            Link *link = dynamic_cast<Link *>(i.next());
            if (link) {
                delete link;
                i.remove();
            }
        }

        qDeleteAll(items);
    }

    void DiagramWindow::cut()
    {
        Node *node = selectedNode();
        if (!node)
            return;

        copy();
        delete node;
    }

    /*
    str字符串的格式是：Node #aa0000 #000080 #ffffff Red herring
    */
    void DiagramWindow::copy()
    {
        Node *node = selectedNode();
        if (!node)
            return;

        QString str = QString("Node %1 %2 %3 %4")
                      .arg(node->textColor().name())
                      .arg(node->outlineColor().name())
                      .arg(node->backgroundColor().name())
                      .arg(node->text());
        QApplication::clipboard()->setText(str);
    }

    void DiagramWindow::paste()
    {
        QString str = QApplication::clipboard()->text();
        QStringList parts = str.split(" ");

        if (parts.count() >= 5 && parts.first() == "Node") {
            Node *node = new Node;
            node->setText(QStringList(parts.mid(4)).join(" "));
            node->setTextColor(QColor(parts[1]));
            node->setOutlineColor(QColor(parts[2]));
            node->setBackgroundColor(QColor(parts[3]));
            setupNode(node);
        }
    }

    /*
    增加maxZ的值，然后会把当前选中的节点的z值设置为maxZ
    */
    void DiagramWindow::bringToFront()
    {
        ++maxZ;
        setZValue(maxZ);
    }

    /*
    减少minZ的值，然后会把当前选中的节点的z值设置为minZ
    */
    void DiagramWindow::sendToBack()
    {
        --minZ;
        setZValue(minZ);
    }

    /*
    如果用户触发lProperties动作，并且只有一个节点被选中，就可以调用Properties对话框。
    这个对话框允许用户修改节点的文字、位置和颜色。
    因为PropertiesDialog可以直接操作一个节点的指针，我们只需将其执行为模态对话框即可，它会自行照料自己。
    如果一个Link被选中，就可以使用Qt内置的QColorDialog::getColor()静态简便函数弹出一个颜色对话框。如果用户
    选择了一种颜色，就将它设置为Link的颜色
    */
    void DiagramWindow::properties()
    {
        Node *node = selectedNode();
        Link *link = selectedLink();

        if (node) {
            PropertiesDialog dialog(node, this);
            dialog.exec();
        } else if (link) {
            QColor color = QColorDialog::getColor(link->color(), this);
            if (color.isValid())
                link->setColor(color);
        }
    }

    void DiagramWindow::updateActions()
    {
        bool hasSelection = !scene->selectedItems().isEmpty();
        bool isNode = (selectedNode() != 0);
        bool isNodePair = (selectedNodePair() != NodePair());

        cutAction->setEnabled(isNode);
        copyAction->setEnabled(isNode);
        addLinkAction->setEnabled(isNodePair);
        deleteAction->setEnabled(hasSelection);
        bringToFrontAction->setEnabled(isNode);
        sendToBackAction->setEnabled(isNode);
        propertiesAction->setEnabled(isNode);

        foreach (QAction *action, view->actions())
            view->removeAction(action);

        foreach (QAction *action, editMenu->actions()) {
            if (action->isEnabled())
                view->addAction(action);
        }
    }

    void DiagramWindow::createActions()
    {
        exitAction = new QAction(tr("E&xit"), this);
        exitAction->setShortcut(tr("Ctrl+Q"));
        connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

        addNodeAction = new QAction(tr("Add &Node"), this);
        addNodeAction->setIcon(QIcon(":/images/node.png"));
        addNodeAction->setShortcut(tr("Ctrl+N"));
        connect(addNodeAction, SIGNAL(triggered()), this, SLOT(addNode()));

        addLinkAction = new QAction(tr("Add &Link"), this);
        addLinkAction->setIcon(QIcon(":/images/link.png"));
        addLinkAction->setShortcut(tr("Ctrl+L"));
        connect(addLinkAction, SIGNAL(triggered()), this, SLOT(addLink()));

        deleteAction = new QAction(tr("&Delete"), this);
        deleteAction->setIcon(QIcon(":/images/delete.png"));
        deleteAction->setShortcut(tr("Del"));
        connect(deleteAction, SIGNAL(triggered()), this, SLOT(del()));

        cutAction = new QAction(tr("Cu&t"), this);
        cutAction->setIcon(QIcon(":/images/cut.png"));
        cutAction->setShortcut(tr("Ctrl+X"));
        connect(cutAction, SIGNAL(triggered()), this, SLOT(cut()));

        copyAction = new QAction(tr("&Copy"), this);
        copyAction->setIcon(QIcon(":/images/copy.png"));
        copyAction->setShortcut(tr("Ctrl+C"));
        connect(copyAction, SIGNAL(triggered()), this, SLOT(copy()));

        pasteAction = new QAction(tr("&Paste"), this);
        pasteAction->setIcon(QIcon(":/images/paste.png"));
        pasteAction->setShortcut(tr("Ctrl+V"));
        connect(pasteAction, SIGNAL(triggered()), this, SLOT(paste()));

        bringToFrontAction = new QAction(tr("Bring to &Front"), this);
        bringToFrontAction->setIcon(QIcon(":/images/bringtofront.png"));
        connect(bringToFrontAction, SIGNAL(triggered()),
                this, SLOT(bringToFront()));

        sendToBackAction = new QAction(tr("&Send to Back"), this);
        sendToBackAction->setIcon(QIcon(":/images/sendtoback.png"));
        connect(sendToBackAction, SIGNAL(triggered()),
                this, SLOT(sendToBack()));

        propertiesAction = new QAction(tr("P&roperties..."), this);
        connect(propertiesAction, SIGNAL(triggered()),
                this, SLOT(properties()));
    }

    void DiagramWindow::createMenus()
    {
        fileMenu = menuBar()->addMenu(tr("&File"));
        fileMenu->addAction(exitAction);

        editMenu = menuBar()->addMenu(tr("&Edit"));
        editMenu->addAction(addNodeAction);
        editMenu->addAction(addLinkAction);
        editMenu->addAction(deleteAction);
        editMenu->addSeparator();
        editMenu->addAction(cutAction);
        editMenu->addAction(copyAction);
        editMenu->addAction(pasteAction);
        editMenu->addSeparator();
        editMenu->addAction(bringToFrontAction);
        editMenu->addAction(sendToBackAction);
        editMenu->addSeparator();
        editMenu->addAction(propertiesAction);
    }

    void DiagramWindow::createToolBars()
    {
        editToolBar = addToolBar(tr("Edit"));
        editToolBar->addAction(addNodeAction);
        editToolBar->addAction(addLinkAction);
        editToolBar->addAction(deleteAction);
        editToolBar->addSeparator();
        editToolBar->addAction(cutAction);
        editToolBar->addAction(copyAction);
        editToolBar->addAction(pasteAction);
        editToolBar->addSeparator();
        editToolBar->addAction(bringToFrontAction);
        editToolBar->addAction(sendToBackAction);
    }

    /*
    获取当前被选中的节点，然后将它的z值设置为z
    */
    void DiagramWindow::setZValue(int z)
    {
        Node *node = selectedNode();
        if (node)
            node->setZValue(z);
    }

    /*
    此函数可以在场景中定位一个新近添加或者复制的节点。
    序列号的用途可以确保新节点被添加到一个不同的位置，而不是放在彼此之上。
    */
    void DiagramWindow::setupNode(Node *node)
    {
        node->setPos(QPoint(80 + (100 * (seqNumber % 5)),
                            80 + (50 * ((seqNumber / 5) % 7))));
        scene->addItem(node);
        ++seqNumber;

        /*清除当前的选中操作，并且将新添加的节点选中*/
        scene->clearSelection();
        node->setSelected(true);
        /*确保新节点比任何其它节点都靠前*/
        bringToFront();
    }

    /*
    获取当前选中的节点
    */
    Node *DiagramWindow::selectedNode() const
    {
        QList<QGraphicsItem *> items = scene->selectedItems();
        if (items.count() == 1) {
            return dynamic_cast<Node *>(items.first());
        } else {
            return 0;
        }
    }

    Link *DiagramWindow::selectedLink() const
    {
        QList<QGraphicsItem *> items = scene->selectedItems();
        if (items.count() == 1) {
            return dynamic_cast<Link *>(items.first());
        } else {
            return 0;
        }
    }

    /*获取选中的两个节点*/
    DiagramWindow::NodePair DiagramWindow::selectedNodePair() const
    {
        QList<QGraphicsItem *> items = scene->selectedItems();
        if (items.count() == 2) {
            Node *first = dynamic_cast<Node *>(items.first());
            Node *second = dynamic_cast<Node *>(items.last());
            if (first && second)
                return NodePair(first, second);
        }
        return NodePair();
    }
