#include "breakpoints.h"

BreakPoints::BreakPoints(QWidget *parent)
    :DebuggerClient(parent)
{

}

BreakPoints::~BreakPoints()
{

}

QStringList BreakPoints::headers() const
{
  return QStringList()<<tr("Number")<<tr("Type")<<("Disposition")<<tr("Enabled")
                     <<tr("Adress")<<tr("Function")<<tr("File")<<tr("Line")<<tr("Condition")<<tr("Hits time");
}

QString BreakPoints::cmd() const
{
  return "info breakpoints";
}

QString BreakPoints::outputFormat() const
{
return "(\\d+)\\s+(\\w+)\\s+(\\w+)\\s(\\w)\\s+(\\S+)\\s\\w+\\s([^\\t]+)at\\s(\\S+):(\\d+)\\r\\n([^\\r])*\\r*\\n*([^\\r])*";
}





