#include "dockwidget.h"

#include <QStyle>
#include <QToolButton>
#include <QHBoxLayout>
#include <QStyleOptionDockWidget>
#include <QPainter>
#include <QToolBar>
#include <QAction>

#include <QSpacerItem>


DockWidget::DockWidget(QWidget *parent) :
    QDockWidget(parent)
{
    setTitleBarWidget(titleBar());
}

QWidget * DockWidget::titleBar()
{    
    QStyleOptionDockWidget opt;
    initStyleOption(&opt);

    QToolBar * tool = new QToolBar("myName");

    tool->setIconSize(QSize(16,16));

    QTabBar * bar = new QTabBar;

    bar->setTabsClosable(true);

    bar->setLayout(wLayout);

    bar->addTab("Text");
    bar->addTab("reus");

    tool->addWidget(bar);

    QAction *action = new
            QAction(style()->standardIcon(QStyle::SP_TitleBarNormalButton, &opt, this),"",this);

    tool->addAction(action);

    action = new
            QAction(style()->standardIcon(QStyle::SP_TitleBarCloseButton, &opt, this),"",this);

    tool->addAction(action);

    action = new QAction(QIcon(":/images/open.png"),"",this);
    tool->addAction(action);

    return tool;
}

