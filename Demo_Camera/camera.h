#ifndef CAMERA_H
#define CAMERA_H

#include <QWidget>

class QCamera;

class Camera : public QWidget
{
    Q_OBJECT

public:
    Camera(QWidget *parent = 0);
    ~Camera();

private:
    QCamera *camera;
};

#endif // CAMERA_H
