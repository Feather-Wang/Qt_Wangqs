#include <QtGui>
#include <QMessageBox>
#include <QApplication>

#include "cell.h"
#include "spreadsheet.h"

Spreadsheet::Spreadsheet(QWidget *parent)
    :QTableWidget(parent)
{
    autoRecalc = true;

    setItemPrototype(new Cell);
    setSelectionMode(ContiguousSelection);

    connect(this, SIGNAL(itemChanged(QTableWidgetItem*)), this, SLOT(somethingChanged()));

    clear();
}

void Spreadsheet::clear()
{
    setRowCount(0);
    setColumnCount(0);
    setRowCount(RowCount);
    setColumnCount(ColumnCount);

    for(int i = 0; i < ColumnCount; ++i)
    {
        QTableWidgetItem *item = new QTableWidgetItem;
        item->setText(QString(QChar('A'+i)));
        setHorizontalHeaderItem(i, item);
    }

    setCurrentCell(0, 0);
}

/*根据给定的行和列返回一个Cell对象*/
Cell *Spreadsheet::cell(int row, int column) const
{
    return static_cast<Cell *>(item(row, column));
}

/*返回给定单元格中的文本*/
QString Spreadsheet::text(int row, int column) const
{
    Cell *c = cell(row, column);
    if( c )
    {
        return c->text();
    }
    else
    {
        return "";
    }
}

/*返回给定单元格中的公式*/
QString Spreadsheet::formula(int row, int column) const
{
    Cell *c = cell(row, column);
    if( c )
    {
        return c->formula();
    }
    else
    {
        return "";
    }
}

/*用于设置给定单元格的公式*/
void Spreadsheet::setFormula(int row, int column, const QString &formula)
{
    Cell *c = cell(row, column);
    if( !c )
    {
        c = new Cell;
        setItem(row, column, c);
    }

    c->setFormula(formula);
}

/*返回当前单元格的位置，它是按照电子制表软件的通常格式，也就是一个列字母后跟上行号的形式来表示这个位置的值*/
QString Spreadsheet::currentLocation() const
{
    return QChar('A' + currentColumn()) + QString::number(currentRow() + 1);
}

/*返回当前单元格的公式*/
QString Spreadsheet::currentFormula() const
{
    return formula(currentRow(), currentColumn());
}

/*如果启动了“auto-recalculate”（自动重新计算），那么somethingChanged()私有槽就会重新计算整个电子制表软件，而且还会发射modified()信号*/
void Spreadsheet::somethingChanged()
{
    if( autoRecalc )
        recalculate();
    emit modified();
}

/*把文件fileName写入到磁盘中*/
bool Spreadsheet::writeFile(const QString &fileName)
{
    QFile file(fileName);
    if( !file.open(QIODevice::WriteOnly) )
    {
        QMessageBox::warning(this, tr("Spreadsheet"), tr("Cannot write file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }
    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_5_6);

    out << quint32(MagicNumber);

    QApplication::setOverrideCursor(Qt::WaitCursor);

    for(int row = 0; row < RowCount; ++row)
    {
        for(int column = 0; column < ColumnCount; ++column)
        {
            QString str = formula(row, column);
            if( !str.isEmpty() )
            {
                out << quint16(row) << quint16(column) << str;
            }
        }
    }

    QApplication::restoreOverrideCursor();

    return true;
}

/*读取一个文件*/
bool Spreadsheet::readFile(const QString &fileName)
{
    QFile file(fileName);
    if( !file.open(QIODevice::ReadOnly) )
    {
        QMessageBox::warning(this, tr("Spreadsheet"), tr("Cannot read file %1:\n%2.").arg(file.fileName()).arg(file.errorString()));
        return false;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_5_6);

    quint32 magic;
    in >> magic;

    if( magic != MagicNumber )
    {
        QMessageBox::warning(this, tr("Spreadsheet"), tr("The file is not a Spreadsheet file."));
        return false;
    }

    clear();

    quint16 row;
    quint16 column;
    QString str;

    QApplication::setOverrideCursor(Qt::WaitCursor);

    while( !in.atEnd() )
    {
        in >> row >> column >> str;
        setFormula(row, column, str);
    }

    QApplication::restoreOverrideCursor();

    return true;
}

void Spreadsheet::cut()
{
    copy();
    del();
}

void Spreadsheet::copy()
{
    qDebug() << "Spreadsheet::copy()";
    /*selectedRange()返回一个选中范围，通过遍历这个范围，可以获取每一个单元格的数据*/
    QTableWidgetSelectionRange range = selectedRange();
    QString str;

    for(int i = 0; i < range.rowCount(); ++i)
    {
        if( i > 0 )
        {
            str += "\n";
        }

        for( int j = 0; j < range.columnCount(); ++j )
        {
            if( j > 0 )
            {
                str += "\t";
            }
            str += formula(range.topRow() + i, range.leftColumn() + j);
        }
    }

    qDebug() << "Spreadsheet::copy() [" << str;
    /*调用QApplication::clipboard()可以使用系统的剪贴板，调用seText就会吧str放在剪贴板中*/
    QApplication::clipboard()->setText(str);
}


void Spreadsheet::paste()
{
    /*获取选中范围*/
    QTableWidgetSelectionRange range = selectedRange();
    /*从剪贴板总获取数据*/
    QString str = QApplication::clipboard()->text();

    qDebug() << "Spreadsheet::paste() : " << str;

    QStringList rows = str.split('\n');
    int numRows = rows.count();
    int numColumns = rows.first().count('\t') + 1;
    qDebug() << "Spreadsheet::paste() : " << numRows << " : " << numColumns;

    if( range.rowCount() * range.columnCount() != 1
            && (range.rowCount() != numRows || range.columnCount() != numColumns))
    {
        QMessageBox::information(this, tr("Spreadsheet"), tr("The information cannot be pasted because the copy and paste areas aren't the same size."));
        return;
    }
    qDebug() << "Spreadsheet::paste() QMessageBox::information() after";

    for( int i = 0; i < numRows; ++i )
    {
        qDebug() << "Spreadsheet::paste(), i=" << i;
        QStringList columns = rows[i].split('\t');
        qDebug() << "Spreadsheet::paste(), split()";
        for( int j = 0; j < numColumns; ++j )
        {
            qDebug() << "Spreadsheet::paste(), j=" << j;
            int row = range.topRow() + i;
            int column = range.leftColumn() + j;
            if( row < RowCount && column < ColumnCount )
            {
                setFormula(row, column, columns[j]);
            }
        }
    }

    qDebug() << "Spreadsheet::paste, somethingChanged()";
    somethingChanged();
}

void Spreadsheet::del()
{
    QList<QTableWidgetItem *> items = selectedItems();
    if( !items.isEmpty() )
    {
        foreach (QTableWidgetItem *item, items) {
            delete item;
        }
        somethingChanged();
    }
}

void Spreadsheet::selectCurrentRow()
{
    selectRow(currentRow());
}

void Spreadsheet::selectCurrentColumn()
{
    selectColumn(currentColumn());
}

/*从光标的右侧开始遍历，查找所有的单元格，知道找到所要查找的文本*/
void Spreadsheet::findNext(const QString &str, Qt::CaseSensitivity cs)
{
    int row = currentRow();
    int column = currentColumn() + 1;

    while( row < RowCount )
    {
        while( column < ColumnCount)
        {
            if( text(row, column).contains(str, cs) )
            {
                /*清空当前选择*/
                clearSelection();
                /*将找到的单元格设为选中状态*/
                setCurrentCell(row, column);
                /*让包含spreadsheet的窗口变成激活状态*/
                activateWindow();
                return;
            }
            ++column;
        }
        column = 0;
        ++row;
    }

    /*发出‘哔’的一声来表示搜索结束*/
    QApplication::beep();
}

/*与findNext相反，findPrevious是向前查找*/
void Spreadsheet::findPrevious(const QString &str, Qt::CaseSensitivity cs)
{
    int row = currentRow();
    int column = currentColumn() - 1;

    while( row >= 0 )
    {
        while( column >= 0 )
        {
            if( text(row, column ).contains(str, cs) )
            {
                clearSelection();
                setCurrentCell(row, column);
                activateWindow();
                return;
            }
            --column;
        }
        column = ColumnCount - 1;
        --row;
    }

    QApplication::beep();
}

void Spreadsheet::recalculate()
{
    for( int row = 0; row < RowCount; ++row )
    {
        for( int column = 0; column < ColumnCount; ++column )
        {
            if( cell(row, column) )
            {
                /*使用setDIrty把每一个单元格标记为需要重新计算*/
                cell( row, column )->setDirty();
            }
        }
    }

    /*使用viewport()->update对这个视口重新绘制整个电子制表软件，然后QTableWidget中的重绘代码就又会对每一个可见单元格调用text()来获得它们中要显示的值*/
    viewport()->update();
}

void Spreadsheet::setAutoRecalculate(bool recalc)
{
    autoRecalc = recalc;
    if( autoRecalc )
    {
        recalculate();
    }
}

void Spreadsheet::sort(const SpreadsheetCompare &compare)
{
    QList<QStringList> rows;
    QTableWidgetSelectionRange range = selectedRange();
    int i;

    for( i = 0; i < range.rowCount(); ++i )
    {
        QStringList row;
        for( int j = 0; j < range.columnCount(); ++j)
        {
            QString str = formula(range.topRow() + i, range.leftColumn() + j);
            if( !str.isEmpty() )
            {
                row.append(str);
                qDebug() << "Spreadsheet::sort before ->" << str;
            }

        }

        rows.append(row);
    }

    qDebug() << "Spreadsheet::sort before";
    qStableSort(rows.begin(), rows.end(), compare);
    qDebug() << "Spreadsheet::sort after";

    for( i = 0; i < range.rowCount(); ++i)
    {
        for( int j = 0; j < range.columnCount(); ++j)
        {
            qDebug() << "Spreadsheet::sort after ->" << rows[i][j];
            setFormula(range.topRow() + i, range.leftColumn() + j, rows[i][j]);
        }
    }

    clearSelection();
    somethingChanged();
}

bool SpreadsheetCompare::operator ()(const QStringList &row1, const QStringList &row2) const
{
    for( int i = 0; i < KeyCount; ++i)
    {
        int column = keys[i];
        if( column != -1 )
        {
            if( row1[column] != row2[column] )
            {
                if( ascending[i] )
                {
                    return row1[column] < row2[column];
                }
                else
                {
                    return row1[column] > row2[column];
                }
            }
        }
    }

    return false;
}

QTableWidgetSelectionRange Spreadsheet::selectedRange() const
{
    QList<QTableWidgetSelectionRange> ranges = selectedRanges();
    qDebug() << "Spreadsheet::selectedRange() : count=" << ranges.count();
    if( ranges.isEmpty() )
    {
        return QTableWidgetSelectionRange();
    }
    return ranges.first();
}
