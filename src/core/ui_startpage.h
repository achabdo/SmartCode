/********************************************************************************
** Form generated from reading UI file 'startpage.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTPAGE_H
#define UI_STARTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartPage
{
public:
    QWidget *scrollAreaWidgetContents;
    QLabel *recent;
    QListWidget *listWidget;
    QPushButton *newproject;
    QPushButton *openproject;

    void setupUi(QScrollArea *StartPage)
    {
        if (StartPage->objectName().isEmpty())
            StartPage->setObjectName(QStringLiteral("StartPage"));
        StartPage->resize(862, 953);
        StartPage->setStyleSheet(QLatin1String("QListWidget:item\n"
"{\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        StartPage->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 860, 951));
        recent = new QLabel(scrollAreaWidgetContents);
        recent->setObjectName(QStringLiteral("recent"));
        recent->setGeometry(QRect(90, 260, 111, 23));
        QFont font;
        font.setFamily(QStringLiteral("Calibri"));
        font.setPointSize(13);
        font.setBold(true);
        font.setWeight(75);
        recent->setFont(font);
        recent->setLayoutDirection(Qt::LeftToRight);
        recent->setStyleSheet(QStringLiteral(""));
        listWidget = new QListWidget(scrollAreaWidgetContents);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(70, 310, 321, 231));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        listWidget->setFont(font1);
        listWidget->setAutoFillBackground(false);
        listWidget->setStyleSheet(QStringLiteral("background-color:transparent"));
        listWidget->setFrameShape(QFrame::NoFrame);
        listWidget->setFrameShadow(QFrame::Sunken);
        listWidget->setLineWidth(1);
        listWidget->setAutoScrollMargin(16);
        listWidget->setAlternatingRowColors(false);
        listWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
        listWidget->setIconSize(QSize(20, 20));
        listWidget->setMovement(QListView::Static);
        listWidget->setProperty("isWrapping", QVariant(false));
        listWidget->setLayoutMode(QListView::SinglePass);
        listWidget->setSpacing(0);
        listWidget->setViewMode(QListView::ListMode);
        listWidget->setModelColumn(0);
        listWidget->setUniformItemSizes(false);
        listWidget->setBatchSize(100);
        listWidget->setWordWrap(true);
        listWidget->setSelectionRectVisible(false);
        listWidget->setSortingEnabled(false);
        newproject = new QPushButton(scrollAreaWidgetContents);
        newproject->setObjectName(QStringLiteral("newproject"));
        newproject->setEnabled(true);
        newproject->setGeometry(QRect(60, 20, 151, 41));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(newproject->sizePolicy().hasHeightForWidth());
        newproject->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setFamily(QStringLiteral("Segoe UI"));
        font2.setPointSize(10);
        font2.setBold(true);
        font2.setUnderline(false);
        font2.setWeight(75);
        newproject->setFont(font2);
        newproject->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral("../../../Abdo/library/abdo/icon/application-file-icone-9762-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        newproject->setIcon(icon);
        newproject->setIconSize(QSize(64, 64));
        newproject->setCheckable(false);
        newproject->setAutoRepeat(false);
        newproject->setAutoExclusive(false);
        newproject->setAutoDefault(false);
        newproject->setDefault(false);
        newproject->setFlat(true);
        openproject = new QPushButton(scrollAreaWidgetContents);
        openproject->setObjectName(QStringLiteral("openproject"));
        openproject->setEnabled(true);
        openproject->setGeometry(QRect(220, 20, 151, 41));
        sizePolicy1.setHeightForWidth(openproject->sizePolicy().hasHeightForWidth());
        openproject->setSizePolicy(sizePolicy1);
        openproject->setFont(font2);
        openproject->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral("../../../Abdo/library/abdo/icon/dossier-icone-8757-128.png"), QSize(), QIcon::Normal, QIcon::Off);
        openproject->setIcon(icon1);
        openproject->setIconSize(QSize(64, 64));
        openproject->setCheckable(false);
        openproject->setAutoRepeat(false);
        openproject->setAutoExclusive(false);
        openproject->setAutoDefault(false);
        openproject->setDefault(false);
        openproject->setFlat(true);
        StartPage->setWidget(scrollAreaWidgetContents);

        retranslateUi(StartPage);

        QMetaObject::connectSlotsByName(StartPage);
    } // setupUi

    void retranslateUi(QScrollArea *StartPage)
    {
        StartPage->setWindowTitle(QApplication::translate("StartPage", "ScrollArea", 0));
        recent->setText(QApplication::translate("StartPage", "Recent Projects", 0));
        newproject->setText(QApplication::translate("StartPage", " New project", 0));
        openproject->setText(QApplication::translate("StartPage", "Open project", 0));
    } // retranslateUi

};

namespace Ui {
    class StartPage: public Ui_StartPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTPAGE_H
