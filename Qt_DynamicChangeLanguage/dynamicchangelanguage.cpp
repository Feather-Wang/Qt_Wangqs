#include "dynamicchangelanguage.h"

#include <QtDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QPushButton>
#include <QLineEdit>
#include <QApplication>

DynamicChangeLanguage::DynamicChangeLanguage(QWidget *parent) : QDialog(parent)
{
    englishButton = new QPushButton(this);
    chineseButton = new QPushButton(this);
    japaneseButton = new QPushButton(this);
    showLanguage = new QLineEdit(this);

    QHBoxLayout *hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(englishButton);
    hboxLayout->addWidget(chineseButton);
    hboxLayout->addWidget(japaneseButton);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(showLanguage);
    layout->addLayout(hboxLayout);

    setLayout(layout);

    connect(englishButton, SIGNAL(clicked(bool)), this, SLOT(switchLanguage()));
    connect(chineseButton, SIGNAL(clicked(bool)), this, SLOT(switchLanguage()));
    connect(japaneseButton, SIGNAL(clicked(bool)), this, SLOT(switchLanguage()));

    qApp->installTranslator(&appTranslator);
    qApp->installTranslator(&qtTranslator);

    retranslateUi();
}


void DynamicChangeLanguage::retranslateUi()
{
    englishButton->setText(tr("en"));
    chineseButton->setText(tr("zh"));
    japaneseButton->setText(tr("ja"));

    showLanguage->setText(tr("set language to English"));

    setWindowTitle(tr("Change language to English"));
}

void DynamicChangeLanguage::switchLanguage()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    QString locale = button->text().toLatin1();
    QString qmPath = "D:\\SoftWare\\QTCreator\\Projects\\Qt_DynamicChangeLanguage";
    qDebug() << "button --> " << locale;
    appTranslator.load("language_" + locale, qmPath);
    qtTranslator.load("qt_" + locale, qmPath);

    retranslateUi();
}
