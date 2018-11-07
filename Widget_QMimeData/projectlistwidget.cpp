#include "projectlistwidget.h"

#include <QtGui>
#include <QApplication>

ProjectListWidget::ProjectListWidget(const QString &name, QWidget *parent)
    :QListWidget(parent)
{
    setAcceptDrops(true);
    addItem(new QListWidgetItem(QIcon(tr(":/images/images/person.png")), name));
}

/*当用户按下鼠标左键时，保存点击的坐标，然后调用QListWidget::mousePressEvent(event)响应默认的操作*/
void ProjectListWidget::mousePressEvent(QMouseEvent *event)
{
    if( event->button() == Qt::LeftButton )
        startPos = event->pos();
    QListWidget::mousePressEvent(event);
}

/*
当鼠标在窗口部件中移动时，
*/
void ProjectListWidget::mouseMoveEvent(QMouseEvent *event)
{
    if( event->buttons() & Qt::LeftButton )
    {
        /*
         * 计算抖动值，获取从原点到当前点之间的距离
         * manhattanLength()是曼哈顿长度，即从坐标原点到该矢量长度快速计算的近似值。
         * 当曼哈顿长度大于或等于QApplication推荐的拖动起始距离值（通常是4个像素），
         * 那么就调用performDrag()以启动拖动操作，
         * 这样可以避免用户因为手握鼠标抖动而产生拖动。
        */
        int distance = (event->pos() - startPos).manhattanLength();
        if( distance >= QApplication::startDragDistance() )
            performDrag();
    }

    /*然后执行默认的操作*/
    QListWidget::mouseMoveEvent(event);
}

/*
创建一个QDrag类的对象，并且把this作为它的父对象。
这个QDrag对象将数据存储在QMimeData对象中。
在这个实例中，我们利用QMimeData::setText()提供了作为text/plain字符串的数据。
QMimeData提供了一些可用于处理最常用拖放类型（诸如图像、URL、颜色等）的函数，
同时也可以处理任意由QByteArrays表示的MIME类型。
QDrag::setPixmap()调用则可以在拖放发生时使图标随光标移动。

QDrag::exec()调用启动并执行拖放操作，直到用户放下或取消此次拖动操作才会停止，
它把所有支持的“拖放操作”（如Qt::CopyAction, Qt::MoveAction, Qt::LinkAction）的组合作为其参数，
并且返回被执行的拖放操作（如果没有执行任何动作，则返回Qt::IgnoreAction）。
至于执行的是哪个动作，取决于放下发送时原窗口部件是否允许、目标是否支持及按下了哪些组合键。
在exec()调用后，Qt拥有拖动对象的所有权并且可以在不需要它的时候删除它
*/
void ProjectListWidget::performDrag()
{
    QListWidgetItem *item = currentItem();
    if( item )
    {
        /*存储拖动的数据*/
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(item->text());

        /*将图标通过QDataStream和QByteArray添加到QDrag中*/
        QByteArray data;
        QDataStream stream(&data, QIODevice::WriteOnly);
        stream << item->icon();
        mimeData->setData("Drag-Icon", data);

        QDrag *drag = new QDrag(this);
        /*设置拖动的数据*/
        drag->setMimeData(mimeData);
        /*拖动时，光标旁边会显示这个QPixmap*/
        drag->setPixmap(QPixmap(":/images/images/person.png"));
        if( drag->exec(Qt::MoveAction) == Qt::MoveAction )
            delete item;
    }
}

/*
ProjectListWidget窗口部件不仅能发起拖动，还可以接收同一个应用程序中来自另一个ProjectListWidget窗口部件的拖动。
如果窗口部件是同一个应用程序的一部分，QRagEnterEvent::source()返回一个启动这个拖动的窗口部件的指针，否则，返回一个空指针。
我们使用qobject_cast<T>()，以确保这个拖动来自ProjectListWidget。
如果一切无误，就告诉Qt预备将该动作认为是一个移动动作。
*/
void ProjectListWidget::dragEnterEvent(QDragEnterEvent *event)
{
    ProjectListWidget *source = qobject_cast<ProjectListWidget *>(event->source());
    if( source && source != this )
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

/*
dragMoveEvent()和dragEnterEvent()的代码基本相同，这样是必须的，因为需要重写QListWidget的函数实现（实际上是QAbstractItemView的函数实现）
*/
void ProjectListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    ProjectListWidget *source = qobject_cast<ProjectListWidget *>(event->source());
    if( source && source != this )
    {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

/*
在dropEvent()中，我们使用QMimeData::text()重新找回拖动的文本并随文本创建一个拖动项。
还需要将事件作为“移动操作”来接受，从而告诉原窗口部件现在可以删除原来的拖动项了。
*/
void ProjectListWidget::dropEvent(QDropEvent *event)
{
    ProjectListWidget *source = qobject_cast<ProjectListWidget *>(event->source());
    if( source && source != this )
    {
        QByteArray data = event->mimeData()->data("Drag-Icon");
        QDataStream stream(&data, QIODevice::ReadOnly);
        QIcon icon;
        stream >> icon;
        addItem(new QListWidgetItem(icon, event->mimeData()->text()));
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}
