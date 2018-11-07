#include "tablemimedata.h"

TableMimeData::TableMimeData(const QTableWidget *tableWidget, const QTableWidgetSelectionRange &range)
{
    myTableWidget = tableWidget;
    myRange = range;
    myFormats << "text/csv" << "text/html" << "text/plain";
}

/*
返回一个由MIME数据对象提供的MIME类型列表。各种格式之间的排列顺序通常是无关联的，但是把“最好的”格式放在最前面是一种不错的习惯。
支持多种格式的应用程序有时将使用第一个与其匹配的格式。
*/
QStringList TableMimeData::formats() const
{
    return myFormats;
}
#include <QApplication>
/*
为给定的MIME类型返回一个数据作为其QVariant。
format参数的值通常是由formats()返回的字符串之一，但是我们并不能这样假设，因为并不是所有的应用程序都对照formats()来检查MIME类型。
由QMimeData提供的获取函数，诸如text()、html()、urls()、imageData()、colorData()、data()，都可以根据retrieveData()而重新实现.
preferredType参数提示我们在QVariant中应该插入哪种类型。此处，如果有必要的话，我们将忽略preferredType参数而任由QMimeData将返回值转换为想要的类型。
*/
QVariant TableMimeData::retrieveData(const QString &mimetype, QVariant::Type preferredType) const
{
    /*
    if( format == "text/plain" )
    {
        return rangeAsPlainText();
    }
    else if( format == "text/csv" )
    {
        return toCsv(rangeAsPlainText());
    }
    else if( format == "text/html" )
    {
        return toHtml(rangeAsPlainText());
    }
    else*/
    {
        return QMimeData::retrieveData(mimetype, preferredType);
    }
    QApplication::clipboard();
}
