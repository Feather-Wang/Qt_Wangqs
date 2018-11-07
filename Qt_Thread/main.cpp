#include <QApplication>

/*通过子类化QThread类，来定义自己的线程函数，通过ThreadDialog来展示了两个线程*/
#include "threaddialog.h"
/*演示了如何通过信号-槽连接，让主线程与次线程进行通信*/
#include "imagewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*
    ThreadDialog dialog;
    dialog.show();
    */

    ImageWindow imageWin;
    imageWin.show();

    return a.exec();
}
