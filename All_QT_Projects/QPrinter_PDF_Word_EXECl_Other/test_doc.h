#ifndef TEST_DOC_H
#define TEST_DOC_H

#include <QWidget>

#include <QAxWidget>
#include <QAxObject>

class test_doc : public QWidget
{
    Q_OBJECT
public:
    explicit test_doc(QWidget *parent = 0);

signals:

public slots:

private:

};


class WordEngine : public QObject
{
    Q_OBJECT
public:
    WordEngine();
    ~WordEngine();

    /*打开Word文件，如果sFile路径为空或错误，则打开新的Word文档，并显示在插入数据时是否显示word文档*/
    bool Open(QString sFile, bool bVisible = true);

    void save(QString sSavePath);

    void close(bool bSave = true);

    /*在标签sLabel处，插入字符串sText*/
    bool replaceText(QString sLabel,QString sText);
    /*在标签sLabel处，插入图片sFile*/
    bool replacePic(QString sLabel,QString sFile);
    /*在表确sLabel处，插入一个表格，表格为row行column列*/
    QAxObject *insertTable(QString sLabel,int row,int column);
    /*在表确sLabel处，插入一个表格，表格为row行column列，并在第一行设置表头信息为headList*/
    QAxObject *insertTable(QString sLabel,int row,int column,QStringList headList);
    /*设置表格table的column列的宽度为width*/
    void setColumnWidth(QAxObject *table,int column, int width);
    /*在表格table中得row行column列的单元，插入数据text*/
    void SetTableCellString(QAxObject *table, int row,int column,QString text);

private:

    QAxObject *m_pWord;      //指向整个Word应用程序
    QAxObject *m_pWorkDocuments;  //指向文档集,Word有很多文档
    QAxObject *m_pWorkDocument;   //指向m_sFile对应的文档，就是要操作的文档

    QString m_sFile;
    bool m_bIsOpen;
    bool m_bNewFile;
};

#endif // TEST_DOC_H
