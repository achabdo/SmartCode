#include "debugger.h"
#include <QDebug>

#include "debuggerclient.h"
#include "breakpoint.h"

Debugger::Debugger(QObject *parent) :
  QObject(parent)
{
  process = new QProcess ;
}

void Debugger::execute(const QString &cmd)
{
  process->write(cmd.toLocal8Bit() + '\n');
}

QString Debugger::executeAndRead(const QString &cmd)
{
  execute(cmd);

  QString out;

  while(process->waitForReadyRead(100))
    out += process->readAllStandardOutput();

  return out;
}

void Debugger::load()
{
  process->start(name(),QStringList() << loadProgramCmd() << _program);
}

void Debugger::run()
{
  execute(runProgramCmd());
}

void Debugger::stop()
{
  executeAndRead(exitCmd());
}

void Debugger::step(Step)
{
  updateClients();
}

void Debugger::setProgram(const QString &pro)
{
  _program = pro;
}

QString Debugger::name() const
{
  return QString();
}

QString Debugger::program() const
{
  return _program;
}

void Debugger::setBreakPoint(BreakPoint *, bool)
{

}

QStringList Debugger::loadProgramCmd() const
{
  return QStringList();
}

QString Debugger::runProgramCmd() const
{
  return QString();
}

QString Debugger::nextLineCmd() const
{
  return QString();
}

QString Debugger::nextInstructionCmd() const
{
  return QString();
}

QString Debugger::stepIntoCmd() const
{
  return QString();
}

QString Debugger::stepOutCmd() const
{
  return QString();
}

QString Debugger::continueCmd() const
{
  return QString();
}

QString Debugger::infoLocalsCmd() const
{
  return QString();
}

QString Debugger::infoGlobalsCmd() const
{
  return QString();
}

QString Debugger::printVariableCmd() const
{
  return QString();
}

QString Debugger::breakPointCmd() const
{
  return QString();
}

QString Debugger::clearBreakPointCmd() const
{
  return QString();
}

QString Debugger::exitCmd() const
{
  return QString();
}

void Debugger::addClient(DebuggerClient *client)
{
  client->setHeaderLabels(client->headers());
  clients << client;
}

void Debugger::updateClients()
{
  foreach(DebuggerClient * client,clients)
    {
      QString out = executeAndRead(client->cmd());
      client->updateClient(out);
    }
}

void Debugger::Continue()
{
  execute(continueCmd());
}

QString Debugger::getType(const QString &varName)
{
  execute(QString("ptype %1").arg(varName));
  process->waitForReadyRead();

  return process->readAllStandardOutput().right(6).trimmed();
}


