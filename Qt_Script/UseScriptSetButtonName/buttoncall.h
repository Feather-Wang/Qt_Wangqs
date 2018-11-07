#ifndef BUTTONCALL_H
#define BUTTONCALL_H

#include <QObject>
#include <QtScript/QScriptable>

class ButtonCall : public QObject, public QScriptable
{
    Q_OBJECT
public:
    explicit ButtonCall(QObject *parent = 0);

signals:

public slots:
    void setText(const QString &text);
};

#endif // BUTTONCALL_H
