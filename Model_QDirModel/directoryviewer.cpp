#include "directoryviewer.h"

#include <QDirModel>
#include <QTreeView>
#include <QHeaderView>
#include <QInputDialog>
#include <QMessageBox>

DirectoryViewer::DirectoryViewer(QWidget *parent)
    : QDialog(parent)
{
    model = new QDirModel;
    /*禁止模型的只读模式，表示模型可以将修改的数据写回文件系统*/
    model->setReadOnly(false);
    /*设置模型的排序规则，目录优先、忽略大小写、以名称排序*/
    model->setSorting(QDir::DirsFirst | QDir::IgnoreCase | QDir::Name);

    treeView = new QTreeView(this);
    /*设置关联的模型*/
    treeView->setModel(model);
    /*设置列头的延展策略，当QTreeViwe的宽度大于所有列的宽度之和时，让（true）最后一列扩展至QTreeView的边界*/
    treeView->header()->setStretchLastSection(true);
    /*设置序号为0的列进行排序，排序方式为升序*/
    treeView->header()->setSortIndicator(0, Qt::AscendingOrder);
    /*在排序的列的列头上显示排序的小箭头*/
    treeView->header()->setSortIndicatorShown(true);


    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    /*获取当前目录在模型中的索引值*/
    QModelIndex index = model->index(QDir::currentPath());
    /*然后展开index索引值的路径*/
    treeView->expand(index);
    /*把视图的视口移动到索引值为index的路径的位置*/
    treeView->scrollTo(index);
    /*让序号为0的列，自动适应内容的宽度，避免因为列的宽度不够，使内容显示为...符号*/
    treeView->resizeColumnToContents(0);
}

DirectoryViewer::~DirectoryViewer()
{

}

/*
获取选中项的索引值
*/
void DirectoryViewer::createDirectory()
{
    /*获取选中项的索引值*/
    QModelIndex index = treeView->currentIndex();
    if( !index.isValid() )
        return;

    QString dirName = QInputDialog::getText(this, tr("Create Directory"), tr("Directory name"));
    if( !dirName.isEmpty() )
    {
        /*创建目录*/
        if( !model->mkdir(index, dirName).isValid() )
        {
            QMessageBox::information(this, tr("Create Directory"), tr("Failed to create the directory"));
        }
    }
}

/*
获取模型中的选中项，判断是否有效
判断选中项是否为目录，是，则删掉，不是，则移除
如果操作失败，则显示一个失败的message
*/
void DirectoryViewer::removeDirectory()
{
    /*获取选中项的索引值*/
    QModelIndex index = treeView->currentIndex();
    if( !index.isValid() )
        return;

    bool ok;
    /*判断是目录，还是普通文件，然后分别调用对应的函数，进行删除*/
    if( model->fileInfo(index).isDir() )
    {
        ok = model->rmdir(index);
    }
    else
    {
        ok = model->remove(index);
    }

    if( !ok )
    {
        QMessageBox::information(this, tr("Remove"), tr("Failed to remove %1").arg(model->fileName(index)));
    }
}
