#ifndef TRACKEDITOR_H
#define TRACKEDITOR_H

#include <QtGui>
#include <QDialog>

#include "track.h"

class QTableWidget;

class TrackEditor : public QDialog
{
    Q_OBJECT

public:
    TrackEditor(QList<Track> *tracks, QWidget *parent);

private:
    QList<Track> *tracks;
    QTableWidget *tableWidget;
};

#endif // TRACKEDITOR_H
