#ifndef BREAKPOINT_H
#define BREAKPOINT_H

#include "build_global.h"
#include <QObject>

class BUILDSHARED_EXPORT BreakPoint : public QObject
{
  Q_OBJECT
public:
  enum BreakPointType
  {
    FileNameAndLineNumber,
    FunctionName,
    MemoryAdress,
    Signal,
    ExceptionThrow,
    ExceptionCatch,
    ThreadStart,
    ThreadExit,
    ThreadJoin,
    ProcessStart,
    ProcessExit,
    ProcessFork,
    ProcessvFork,
    ProcessExecuted,
    LoadLibrary,
    UnloadLibrary
  };

  enum ConditionType{isTrue,VariableChanged,NoCondition};

  explicit BreakPoint(const QString &fileName, int line, QObject *parent = 0);

  ~BreakPoint();

  bool isEnabled() const;

  QString fileName()const;
  int line()const;

  void setConditionType(ConditionType cType);

  QString commande() const;
  ConditionType conditionType()const;

  void setIgnoreCount(int count);
  int ignoreCount() const;


  BreakPointType type()const;
  QString condition() const;
  QString function() const;
  QString memoryAdress() const;
signals:

public slots:
  void setLine(const int &line);
  void setFileName(const QString &fileName);
  void setFunction(const QString &func);
  void setMemoryAdresse(const QString & adress);
  void setCondition(const QString &condition);

  void setEnabled(bool _enabled);
  void setType(BreakPointType bType);
private slots:

private:
  QString _fileName;
  QString _condition;
  QString _function;
  QString _memoryAdress;

  int _line;
  int _ignoreCount;

  bool enabled;

  ConditionType _conditionType;
  BreakPointType breakPointType;
};

#endif // BREAKPOINT_H
