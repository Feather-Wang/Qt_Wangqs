#include "finddialog.h"

/*首先，需要包含该头文件，该头文件包含了Qt GUI类的定义*/
#include <QtGui>

#include <QHBoxLayout>
#include <QVBoxLayout>

FindDialog::FindDialog(QWidget *parent)
    : QDialog(parent)
{
    /*tr()函数可以把字符串翻译成其它语言的标记，每一个QObject对象以及包含有Q_OBJECT宏的子类中都有这个函数的声明，尽管也许并没有将你的应用程序立即翻译成其它语言的打算，但是在每一个用户可见的字符串周围使用tr()函数还是一个很不错的习惯*/
    /*在下面的字符串中，有一些&字符，该字符表示快捷键，例如"Find &what:"，表示快捷键Alt+W，"Match &case"表示快捷键Alt+C，当按下快捷键，就相当于触发了对应的按键*/
    label = new QLabel(tr("Find &what:"));
    lineEdit = new QLineEdit;
    /*将lineEdit设置为label的"伙伴", 所谓“伙伴（buddy）”就是一个窗口部件，它可以在按下标签的快捷键时接收焦点（focus），所以当用户按下label的快捷键Alt+W时，焦点就会移动到lineEdit这个行编辑器上*/
    label->setBuddy(lineEdit);

    caseCheckBox = new QCheckBox(tr("Match &case"));
    backwardCheckBox = new QCheckBox(tr("Search &backward"));

    findButton = new QPushButton(tr("&Find"));
    /*将findButton设置为这个对话框默认的按钮，当用户按下Enter键时默认相当于按下了findButton按钮*/
    findButton->setDefault(true);
    /*禁用了findButton按钮，当禁用了一个窗口部件后，它通常会显示为灰色，并且不能和用户发生交互操作*/
    findButton->setEnabled(false);

    closeButton = new QPushButton(tr("Close"));

    /*设置信号和槽，这里，因为FindDialog集成了QDialog，而QDialog又集成QObject，所以这里就省略了connect函数前面的QObject::前缀*/
    connect(lineEdit, SIGNAL(textChanged(const QString &)), this, SLOT(enableFindButton(const QString &)));
    connect(findButton, SIGNAL(clicked()), this, SLOT(findClicked()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));

    /*创建布局管理器，将控件添加到布局管理器中*/

    /*下面的布局管理器一共有四个，该窗口控件的界面布局一共分为三部分，先将窗口分为左右两部分，再把左部分分为上下两部分，最后通过一个主布局管理器将这三部分进行整合成一个布局管理器*/
    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(label);
    topLeftLayout->addWidget(lineEdit);

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addWidget(caseCheckBox);
    leftLayout->addWidget(backwardCheckBox);

    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(findButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    /*让当前的窗口控件，加载这个布局管理器*/
    setLayout(mainLayout);

    /*设置对话框的标题内容*/
    setWindowTitle(tr("Find"));
    /*并让窗口具有一个固定的高度，这是因为在对话框的垂直方向上再没有其他窗口部件可以去占用所多出的空间了*/
    /*sizeHint()函数可以返回一个窗口部件所“理想”的尺寸大小，它属于QWidget类*/
    setFixedHeight(sizeHint().height());
}

/*slot槽*/
void FindDialog::findClicked()
{
    /*当该slot被调用时，会根据backwardCheckBox的取值，发送不同的信号*/
    QString text = lineEdit->text();
    Qt::CaseSensitivity cs = caseCheckBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

    /*emit关键字，表示发送信号，它也会被C++预处理器转换成标准的C++代码*/
    if(backwardCheckBox->isChecked())
    {
        emit findPrevious(text, cs);
    }
    else
    {
        emit findNext(text, cs);
    }
}

/*slot槽*/
void FindDialog::enableFindButton(const QString &text)
{
    /*findButton按钮，默认是不可用的，当lineEdit内容发生变化时，就会发送textChanged()信号，执行该slot，判断lineEdit是否为空，如果不为空，则使能findButton按钮*/
    findButton->setEnabled(!text.isEmpty());
}
