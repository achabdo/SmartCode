#ifndef DEBUGGERCLIENTWIDGET_H
#define DEBUGGERCLIENTWIDGET_H

#include "build_global.h"

#include <QDockWidget>

class Debugger;

class BUILDSHARED_EXPORT DebuggerClientWidget : public QDockWidget
{
  Q_OBJECT

public:
    explicit DebuggerClientWidget(const QString &title,Debugger * debugger, QWidget *parent = 0);
    ~DebuggerClientWidget();

signals:

public slots:
private:
   void addClients(Debugger *debugger);
};

#endif // DEBUGGERCLIENT_H
