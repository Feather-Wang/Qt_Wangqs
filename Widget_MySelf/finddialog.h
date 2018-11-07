#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

/*这里使用class关键字声明类，因为在这个头文件中，只定义了指针，而没有在头文件中访问它们，所以也无需知道这些类的完整定义*/
//class QCheckBox;
#include <QCheckBox>
//class QLabel;
#include <QLabel>
//class QLineEdit;
#include <QLineEdit>
//class QPushButton;
#include <QPushButton>

class FindDialog : public QDialog
{
    /*对于所有定义了信号和槽的类，在类定义开始处的Q_OBJECT宏都是必需的*/
    /*由于该类包含了Q_OBJECT宏，所以由qmake生成的makefile将会自动包含一些运行moc的规则，moc是指Qt的元对象编译器，即meta-object compiler。为了使moc能够正常运行，必须把类定义从实现文件中分离出来并放到头文件中。由moc生成的代码会包含这个头文件，并且会添加一些特殊的C++代码。*/
    /*必须对使用Q_OBJECT宏的类运行moc，由于qmake会自动在makefile中添加这些必要的规则，所以这并不成问题，但是如果忘记了使用qmake重新生成makefile文件，并且也没有重新运行moc，那么连接程序就会报错，指出你声明了一些函数但是却没有实现它们，这些信息可能是相当不明确的*/
    Q_OBJECT
public:
    /*典型的Qt窗口部件类的定义方式，parent参数指定了它的父窗口部件，默认是一个指针，意味着该控件没有父对象*/
    FindDialog(QWidget *parent = 0);

signals:
    /*signals部分声明了当用户单击Find按钮时对话框所发送的两个信号，如果向前查询（search backward）选项生效，对话框就发送findPrevious()信号，否则就发送findNext()信号*/
    /*signals关键字实际上是一个宏，C++预处理器会在编译程序找到它之前把它转换成标准C++代码。*/
    /*Qt::CaseSensitivity是一个枚举类型，用于判断是否区分大小写，有Qt::CaseSensitive和Qt::CaseInsensitive两个取值*/
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);

private slots:
    /*slots关键字实际上也是一个宏，也可以扩展成C++编译程序可以处理的一种结构形式*/
    /*slots关键字用于声明槽*/
    void findClicked();
    void enableFindButton(const QString &text);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QCheckBox *caseCheckBox;
    QCheckBox *backwardCheckBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};

#endif // FINDDIALOG_H
