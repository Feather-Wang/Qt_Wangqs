#include "camera.h"

#include <QCamera>
#include <QCameraViewfinder>

Camera::Camera(QWidget *parent)
    : QWidget(parent)
{
    this->resize(600,400);

    QCameraViewfinder *view_finder = new QCameraViewfinder(this);

    camera = new QCamera;
    camera->setViewfinder(view_finder);

    camera->start();
}

Camera::~Camera()
{

}
