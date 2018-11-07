#ifndef USEDESIGNERWINDOW_H
#define USEDESIGNERWINDOW_H

#include <QDialog>
/*在这里添加由qt designer生成的ui的头文件，规则为ui_<ui name>.h，uic工具可以将useDesignerWindow.ui文件转换成C++并且将转换结果存储在ui_useDesignerWindow.h文件中，命令uic useDesignerWindow.ui -o ui_useDesignerWindow.h*/
#include "ui_useDesignerWindow.h"

/*在这里使用了public继承，这是因为我们想在该对话框的外面访问该对话框的窗口部件*/
/*这里使用的useDesignerWindow是ui_useDesignerWindow.h文件中的类，类名在使用qt designer工具创建窗口时，可以指定*/
class useDesignerWindow : public QDialog, public Ui::useDesignerWindow
{
    Q_OBJECT

public:
    useDesignerWindow(QWidget *parent = 0);

private slots:
    void on_lineEdit_textChanged();
};

#endif // USEDESIGNERWINDOW_H
