#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include "gui_global.h"

#include <QDockWidget>
#include <QAbstractButton>
#include <QTabBar>

class GUISHARED_EXPORT DockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit DockWidget(QWidget *parent = 0);
    
signals:
    
public slots:

private slots:

private:
   QWidget *titleBar();
};

#endif // DOCKWIDGET_H
