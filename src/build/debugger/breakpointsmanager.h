#ifndef BREAKPOINTSMANAGER_H
#define BREAKPOINTSMANAGER_H

#include "build_global.h"
#include <QObject>

class BreakPoint;

class BUILDSHARED_EXPORT BreakPointsManager : public QObject
{
  Q_OBJECT
public:
  explicit BreakPointsManager(QObject *parent = 0);
  ~BreakPointsManager();

  BreakPoint *addBreakPoint(const QString &fileName, int line);

  QList<BreakPoint*> toBreakPoints() const;
  BreakPoint *breakPoint(const QString &fileName, int line);
signals:

public slots:


  void removeBreakPoint(const QString &fileName, int line);
  void toggleBreakPoint(const QString &fileName, int line, bool isToggled);
  void editBreakPoint(const QString &fileName, int line);
private:



  QList<BreakPoint*> breakPoints;
};

#endif // BREAKPOINTSMANAGER_H
