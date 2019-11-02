#ifndef GDB_H
#define GDB_H

#include "build_global.h"

#include "debugger.h"

class BUILDSHARED_EXPORT GDB : public Debugger
{
    Q_OBJECT
public:
    explicit GDB(QObject *parent = 0);
    ~GDB();

  void stop();
  void step(Step stepType);

  void run();

  QString name() const;
  QString executeAndRead(const QString &cmd);

signals:

public slots:

  void setBreakPoint(BreakPoint *breakPoint, bool isToggled);

protected:
  QStringList loadProgramCmd() const;
  QString runProgramCmd() const;
  QString nextLineCmd() const;
  QString nextInstructionCmd() const;
  QString stepIntoCmd() const;
  QString stepOutCmd() const;
  QString continueCmd() const;
  QString breakPointCmd() const;
  QString clearBreakPointCmd() const;
  QString exitCmd() const;

};

#endif // GDB_H
