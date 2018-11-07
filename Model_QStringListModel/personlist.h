#ifndef PERSONLIST_H
#define PERSONLIST_H

#include <QWidget>

class QStringListModel;
class QListView;

class PersonList : public QWidget
{
    Q_OBJECT

public:
    PersonList(QWidget *parent = 0);
    ~PersonList();

    QStringList persons() const;

private:
    QStringListModel *model;
    QListView *listView;

public slots:
    void insert();
    void del();
};

#endif // PERSONLIST_H
