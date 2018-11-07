#ifndef IMAGEWINDOW_H
#define IMAGEWINDOW_H

#include <QMainWindow>
#include "transactionthread.h"

class QAction;
class QLabel;

class ImageWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ImageWindow(QWidget *parent = 0);

private slots:
    void flipHorizontally();
    void flipVertically();
    void ShowImage();

private:
    void loadFile(const QString &fileName);

    TransactionThread thread;
    QLabel *imageLabel;

    QAction *flipHorizontallyAction;
    QAction *flipVerticallyAction;
};

#endif // IMAGEWINDOW_H
