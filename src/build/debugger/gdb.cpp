#include "gdb.h"
#include "breakpoint.h"
#include <QDebug>

GDB::GDB(QObject *parent) : Debugger(parent)
{

}

GDB::~GDB()
{

}

void GDB::stop()
{
  Debugger::stop();
  execute("y");
}

void GDB::step(Debugger::Step stepType)
{
  QRegExp lineReg("\\d+");

  switch(stepType)
    {
    case NextLine:
      lineReg.indexIn(executeAndRead(nextLineCmd()));
    case NextInstruction:
      lineReg.indexIn(executeAndRead(nextInstructionCmd()));
    case StepIn:
      lineReg.indexIn(executeAndRead(stepIntoCmd()));
    case StepOut:
      lineReg.indexIn(executeAndRead(stepOutCmd()));
    }

  int line;
  line = lineReg.cap(0).toInt();

  if(line != 0)
    emit currentLineChanged(line - 1);

  Debugger::step(stepType);
}

void GDB::run()
{
  execute("set new-console on");
  Debugger::run();
}

QString GDB::name() const
{
  return "gdb";
}

QString GDB::executeAndRead(const QString &cmd)
{
  return Debugger::executeAndRead(cmd).remove("(gdb)").trimmed();

}

void GDB::setBreakPoint(BreakPoint * breakPoint, bool isToggled)
{
  switch(breakPoint->type())
    {
    case  BreakPoint::FileNameAndLineNumber:

      if(isToggled)
        {
          execute(QString("%1 %2:%3").arg(breakPointCmd())
                  .arg(breakPoint->fileName()).arg(breakPoint->line()));
        }
      else
        {
          execute(QString("%1 %2:%3").arg("clear")
                  .arg(breakPoint->fileName()).arg(breakPoint->line()));
        }
      break;
    case BreakPoint::FunctionName :
      execute(QString("%1 %2").arg(breakPointCmd())
              .arg(breakPoint->function()));
      break;
   case BreakPoint::MemoryAdress:
      execute(QString("%1 %2").arg(breakPointCmd())
              .arg(breakPoint->memoryAdress()));
          break;
    default:
      break;
    }
}

QStringList GDB::loadProgramCmd() const
{
  return QStringList ()<<"-q";
}

QString GDB::runProgramCmd() const
{
  return "run";
}

QString GDB::nextLineCmd() const
{
  return "next";
}

QString GDB::nextInstructionCmd() const
{
  return "nexti";
}

QString GDB::stepIntoCmd() const
{
  return "step";
}

QString GDB::stepOutCmd() const
{
  return "until";
}

QString GDB::continueCmd() const
{
  return "continue";
}

QString GDB::breakPointCmd() const
{
  return "break";
}

QString GDB::clearBreakPointCmd() const
{
  return "clear";
}

QString GDB::exitCmd() const
{
  return "quit";
}
