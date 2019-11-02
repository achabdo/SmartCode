#include "debuggerclientwidget.h"

#include "debugger.h"
#include "watches.h"

#include "breakpoints.h"
#include "registres.h"
#include "threads.h"
#include "disassembly.h"
#include "stack.h"
#include "examinememory.h"
#include "modules.h"

DebuggerClientWidget::DebuggerClientWidget(const QString &title,Debugger *debugger
                                           , QWidget *parent) : QDockWidget(title,parent)
{
  addClients(debugger);
}

DebuggerClientWidget::~DebuggerClientWidget()
{

}

void DebuggerClientWidget::addClients(Debugger *debugger)
{
  auto tab = new QTabWidget;

  auto breakPoints = new BreakPoints;
  tab->addTab(breakPoints,tr("Breakpoints"));

  auto disassembly = new Disassembly;
  tab->addTab(disassembly,tr("Disa"));

  auto watches = new Watches;
  tab->addTab(watches,"watches");

  auto registres = new Registres;
  tab->addTab(registres,"Registres");

  auto threads = new Threads;
  tab->addTab(threads,"Threads");

  auto stack = new Stack;
  tab->addTab(stack,"Stack");

  auto examineMemory = new ExamineMemory(debugger);
  tab->addTab(examineMemory,"Examine memory");

  auto modules = new Modules;
  tab->addTab(modules,"Modules");

  setWidget(tab);

  debugger->addClient(breakPoints);
  debugger->addClient(watches);
  debugger->addClient(registres);
  debugger->addClient(threads);
  debugger->addClient(disassembly);
  debugger->addClient(stack);
  debugger->addClient(modules);
}

