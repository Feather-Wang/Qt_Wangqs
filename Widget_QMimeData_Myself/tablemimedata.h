#ifndef TABLEMIMEDATA_H
#define TABLEMIMEDATA_H

#include <QMimeData>
#include <QTableWidgetSelectionRange>

class QTableWidget;

class TableMimeData : public QMimeData
{
    Q_OBJECT

public:
    TableMimeData(const QTableWidget *tableWidget, const QTableWidgetSelectionRange &range);

    const QTableWidget *tableWidget() const { return myTableWidget; }
    QTableWidgetSelectionRange range() const { return myRange; }
    QStringList formats() const;

protected:
    QVariant retrieveData(const QString &mimetype, QVariant::Type preferredType) const;

private:
    static QString toHtml(const QString &plainText);
    static QString toCsv(const QString &plainText);

    QString text(int row, int column) const;
    QString rangeAsPlainText() const;
    const QTableWidget *myTableWidget;
    QTableWidgetSelectionRange myRange;
    QStringList myFormats;
};

#endif // TABLEMIMEDATA_H
