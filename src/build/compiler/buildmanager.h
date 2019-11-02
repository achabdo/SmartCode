#ifndef BUILDMANAGER_H
#define BUILDMANAGER_H

#include "build_global.h"

#include <QObject>
#include <QProcess>
#include <QByteArray>

class CompilerSetting;

class BUILDSHARED_EXPORT BuildManager : public QObject
{
  Q_OBJECT
public:

  explicit BuildManager(CompilerSetting *s,QObject *parent = 0);

  bool build();

  void clean();

  QStringList toOutput();

  void setMakeFile(const QString &makefile);
  void setSourceFile(const QString &sourceFile);

  void setWorkingDir(const QString &workingDir);
  QString getWorkingDir() const;

  bool hasError();
  void abort(const QString &exeName);
  bool executeProgram(const QString &program, const QString &arguments, const QString &workingDir, bool runInTerminal = false);

  CompilerSetting *Setting() const;

  bool programCompiled(const QString &destDirTarget) const;

  bool useShadowBuild() const;
  void setUseShadowBuild(bool useShadowBuild);

signals:
  void newStandardError( const QString &err);
  void newStandardOutput(const QString &out);
  void newRunStandardError( const QString &err);
  void newRunStandardOutput(const QString &out);

  void programFinished(const QString &exitCode);

public slots:
  void getProgramExitCode(int exitCode);
private slots:
  void standardError();
  void standardOutput();

  void runStandardError();
  void runStandardOutput();

private:
  QProcess *compileProcess;
  QProcess *runProcess;

  QString compiler;
  QString makeFile;
  QString _sourceFile;
  QString workingDir;

  bool getError;
  bool _useShadowBuild;

  CompilerSetting *setting;
};
#endif // BUILDMANAGER_H
