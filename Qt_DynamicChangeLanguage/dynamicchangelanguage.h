#ifndef DYNAMICCHANGELANGUAGE_H
#define DYNAMICCHANGELANGUAGE_H

#include <QDialog>
#include <QTranslator>
class QPushButton;
class QLineEdit;

class DynamicChangeLanguage : public QDialog
{
    Q_OBJECT
public:
    explicit DynamicChangeLanguage(QWidget *parent = 0);

    void retranslateUi();

signals:

public slots:
    void switchLanguage();

private:
    QPushButton *englishButton;
    QPushButton *chineseButton;
    QPushButton *japaneseButton;
    QLineEdit *showLanguage;

    QTranslator appTranslator;
    QTranslator qtTranslator;
};

#endif // DYNAMICCHANGELANGUAGE_H
