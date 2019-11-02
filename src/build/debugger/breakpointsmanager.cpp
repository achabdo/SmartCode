#include "breakpointsmanager.h"
#include "breakpoint.h"
#include "breakpointwidget.h"

#include <QApplication>

BreakPointsManager::BreakPointsManager(QObject *parent) : QObject(parent)
{

}

BreakPointsManager::~BreakPointsManager()
{

}

void BreakPointsManager::toggleBreakPoint(const QString &fileName,int line,bool isToggled)
{
  if(isToggled)
    addBreakPoint(fileName,line);
  else
    removeBreakPoint(fileName,line);
}

BreakPoint * BreakPointsManager::addBreakPoint(const QString &fileName,int line)
{
  BreakPoint * breakPoint = new BreakPoint(fileName,line);

  breakPoints << breakPoint;

  return breakPoint;
}

QList<BreakPoint *> BreakPointsManager::toBreakPoints() const
{
  return breakPoints;
}

BreakPoint * BreakPointsManager::breakPoint(const QString &fileName,int line)
{
  foreach(BreakPoint *breakP,breakPoints)
    {
      if(breakP->fileName() == fileName && breakP->line() == line)
        return breakP;
    }

  return 0;
}

void BreakPointsManager::removeBreakPoint(const QString &fileName,int line)
{
  foreach(BreakPoint * breakP,breakPoints)
    {
      if(breakP->fileName() == fileName && breakP->line() == line)
        breakPoints.removeOne(breakP);
    }
}

void BreakPointsManager::editBreakPoint(const QString &fileName,int line)
{
  foreach(BreakPoint *breakP,breakPoints)
    {
      if(breakP->fileName() == fileName && breakP->line() == line)
        {
          BreakPointWidget * breakPointWidget = new BreakPointWidget(breakP,qApp->activeWindow());
          breakPointWidget->exec();
          break;
        }

    }
}

