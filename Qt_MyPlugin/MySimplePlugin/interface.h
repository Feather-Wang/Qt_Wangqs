#ifndef INTERFACE_H
#define INTERFACE_H

class InterFace
{
public:
    /*纯虚函数，提供一个统一的接口，在后续通过这个类头像类，间接的调用插件重新实现的该纯虚函数*/
    virtual QString echo(const QString &message) = 0;
};

QT_BEGIN_NAMESPACE

#define InterFace_iid "org.qt-project.Qt.Examples.InterFace"

Q_DECLARE_INTERFACE(InterFace, InterFace_iid)
QT_END_NAMESPACE

#endif // INTERFACE_H
