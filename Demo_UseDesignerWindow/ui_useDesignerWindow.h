/********************************************************************************
** Form generated from reading UI file 'useDesignerWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USEDESIGNERWINDOW_H
#define UI_USEDESIGNERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_useDesignerWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QWidget *useDesignerWindow)
    {
        if (useDesignerWindow->objectName().isEmpty())
            useDesignerWindow->setObjectName(QStringLiteral("useDesignerWindow"));
        useDesignerWindow->resize(314, 82);
        verticalLayout = new QVBoxLayout(useDesignerWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(useDesignerWindow);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(useDesignerWindow);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        okButton = new QPushButton(useDesignerWindow);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setEnabled(false);

        horizontalLayout_2->addWidget(okButton);

        cancelButton = new QPushButton(useDesignerWindow);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_2->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout_2);

#ifndef QT_NO_SHORTCUT
        label->setBuddy(lineEdit);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineEdit, okButton);
        QWidget::setTabOrder(okButton, cancelButton);

        retranslateUi(useDesignerWindow);

        okButton->setDefault(true);


        QMetaObject::connectSlotsByName(useDesignerWindow);
    } // setupUi

    void retranslateUi(QWidget *useDesignerWindow)
    {
        useDesignerWindow->setWindowTitle(QApplication::translate("useDesignerWindow", "Use Qt Designer", 0));
        label->setText(QApplication::translate("useDesignerWindow", "&Cell Location:", 0));
        okButton->setText(QApplication::translate("useDesignerWindow", "PushButton", 0));
        cancelButton->setText(QApplication::translate("useDesignerWindow", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class useDesignerWindow: public Ui_useDesignerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USEDESIGNERWINDOW_H
