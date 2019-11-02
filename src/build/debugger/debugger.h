#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "build_global.h"

#include <QObject>
#include <QProcess>

class CompilerSetting;
class DebuggerClient;
class BreakPoint;

class BUILDSHARED_EXPORT Debugger : public QObject
{
  Q_OBJECT
public:
  enum Step {NextLine,NextInstruction,StepIn,StepOut};

  explicit Debugger(QObject *parent = 0);

  void setProgram(const QString &pro);

  virtual QString name() const;

  virtual void load();
  virtual void run();
  virtual void stop();
  virtual void step(Step stepType);

  virtual void Continue();

  void execute(const QString &cmd);

  virtual QString executeAndRead(const QString &cmd);

  QString getType(const QString &varName);

  void addClient(DebuggerClient * client);

  QString program() const;

signals:
  void currentLineChanged(int line);

public slots:
  virtual void setBreakPoint(BreakPoint *breakPoint, bool isToggled);
protected:

  virtual QStringList loadProgramCmd() const;
  virtual QString runProgramCmd() const;
  virtual QString nextLineCmd() const;
  virtual QString nextInstructionCmd() const;
  virtual QString stepIntoCmd() const;
  virtual QString stepOutCmd() const;
  virtual QString continueCmd() const;
  virtual QString infoLocalsCmd() const ;
  virtual QString infoGlobalsCmd() const;
  virtual QString printVariableCmd() const;
  virtual QString breakPointCmd() const;
  virtual QString clearBreakPointCmd() const;
  virtual QString exitCmd() const;


private:

  QProcess * process;
  QString _program;

  CompilerSetting* compilerSetting;

  void updateClients();

  QList<DebuggerClient*> clients;
};

#endif // DEBUGGER_H
