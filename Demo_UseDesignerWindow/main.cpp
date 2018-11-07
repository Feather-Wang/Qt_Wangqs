#include <QApplication>

#include "usedesignerwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*在这里，将useDesignerWindow的ui加载和窗口部件的处理，都封装到了useDesignerWindow类中*/
    useDesignerWindow *dialog = new useDesignerWindow;
    dialog->show();

    return a.exec();
}
