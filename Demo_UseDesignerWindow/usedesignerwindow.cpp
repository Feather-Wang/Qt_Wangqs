#include <QtGui>

#include <usedesignerwindow.h>

useDesignerWindow::useDesignerWindow(QWidget *parent)
    :QDialog(parent)
{
    /*调用setupUi来初始化窗口，setupUi还会自动将那些符合on_objectName_signalName()命名惯例的任意槽与相应的objectName的signalName()信号相连接，在这个例子中就意味这默认调用了connect(lineEdit, SIGNAL(textChanged()), this, SLOT(on_lineEdit_textChanged()))*/
    setupUi(this);

    /*设置一个检验器来限制输入的范围，Qt提供了三种内置检验器类：QIntValidator、QDoubleValidator、QRegExpValidator*/
    QRegExp regExp("[A-Za-z][1-9][0-9]{0,2}");
    /*这里通过把this传递给QRegExpValidator的构造函数，使它成为useDesignerWindow对象的一个子对象，这样就不用担心有关删除QRegExpValidator的事情了，当删除它的父对象时，它也会被自动删除*/
    lineEdit->setValidator(new QRegExpValidator(regExp, this));

    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void useDesignerWindow::on_lineEdit_textChanged()
{
    okButton->setEnabled(lineEdit->hasAcceptableInput());
}
