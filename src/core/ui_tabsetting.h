/********************************************************************************
** Form generated from reading UI file 'tabsetting.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TABSETTING_H
#define UI_TABSETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TabSetting
{
public:
    QGridLayout *gridLayout;
    QPushButton *add;
    QPushButton *clear;
    QVBoxLayout *TabLayout;
    QPushButton *del;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *TabSetting)
    {
        if (TabSetting->objectName().isEmpty())
            TabSetting->setObjectName(QStringLiteral("TabSetting"));
        TabSetting->resize(646, 368);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(TabSetting->sizePolicy().hasHeightForWidth());
        TabSetting->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(TabSetting);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        add = new QPushButton(TabSetting);
        add->setObjectName(QStringLiteral("add"));

        gridLayout->addWidget(add, 1, 0, 1, 1);

        clear = new QPushButton(TabSetting);
        clear->setObjectName(QStringLiteral("clear"));

        gridLayout->addWidget(clear, 1, 3, 1, 1);

        TabLayout = new QVBoxLayout();
        TabLayout->setObjectName(QStringLiteral("TabLayout"));

        gridLayout->addLayout(TabLayout, 0, 0, 1, 4);

        del = new QPushButton(TabSetting);
        del->setObjectName(QStringLiteral("del"));

        gridLayout->addWidget(del, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 2, 1, 1);

        add->raise();
        del->raise();
        clear->raise();

        retranslateUi(TabSetting);

        QMetaObject::connectSlotsByName(TabSetting);
    } // setupUi

    void retranslateUi(QWidget *TabSetting)
    {
        TabSetting->setWindowTitle(QApplication::translate("TabSetting", "Form", 0));
        add->setText(QApplication::translate("TabSetting", "Add", 0));
        clear->setText(QApplication::translate("TabSetting", "Clear", 0));
        del->setText(QApplication::translate("TabSetting", "Delete", 0));
    } // retranslateUi

};

namespace Ui {
    class TabSetting: public Ui_TabSetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TABSETTING_H
