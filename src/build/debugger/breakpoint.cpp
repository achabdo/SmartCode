#include "breakpoint.h"

BreakPoint::BreakPoint(const QString &fileName,int line,QObject *parent) : QObject(parent),
  enabled(true),
  _conditionType(NoCondition),
  _ignoreCount(0),
  breakPointType(FileNameAndLineNumber)
{
  _fileName = fileName;
  _line = line;
}

BreakPoint::~BreakPoint()
{

}

void BreakPoint::setCondition(const QString &condition)
{
  _condition = condition;
}

void BreakPoint::setFileName(const QString &fileName)
{
  _fileName = fileName ;
}

void BreakPoint::setFunction(const QString &func)
{
  _function = func;
}

void BreakPoint::setMemoryAdresse(const QString &adress)
{
  _memoryAdress = adress;
}

void BreakPoint::setLine(const int &line)
{
  _line = line;
}

void BreakPoint::setEnabled(bool _enabled)
{
  enabled = _enabled;
}

void BreakPoint::setType(BreakPoint::BreakPointType bType)
{
  breakPointType = bType;
}

bool BreakPoint::isEnabled()const
{
  return enabled;
}

QString BreakPoint::fileName() const
{
  return _fileName;
}

int BreakPoint::line() const
{
  return _line;
}

int BreakPoint::ignoreCount() const
{
  return _ignoreCount;
}

BreakPoint::BreakPointType BreakPoint::type() const
{
  return breakPointType;
}

QString BreakPoint::condition() const
{
  return _condition;
}

QString BreakPoint::function() const
{
  return _function;
}

QString BreakPoint::memoryAdress() const
{
  return _memoryAdress;
}

void BreakPoint::setConditionType(BreakPoint::ConditionType cType)
{
  _conditionType = cType;
}


BreakPoint::ConditionType BreakPoint::conditionType() const
{
  return _conditionType;
}

void BreakPoint::setIgnoreCount(int count)
{
  _ignoreCount = count;
}


