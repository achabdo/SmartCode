// Copyright (C) 2014  by Achrouf Abdeour <achroufabdenour@gmail.com>
// Auteur Achrouf Abdenour

// This File is part of SmartCode

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or (at
// your option) any later version.
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
// You should have received a copy of the GNU General Public License
// along with this program. If not, see http://www.gnu.org/licenses/.

#include <bases.h>
#include <compiler/compiler.h>

#include "buildmanager.h"
#include "compilersetting.h"

const char luncher[] = "consoleluncher.exe";

BuildManager::BuildManager(CompilerSetting * s,QObject *parent) :
  QObject(parent)
{
  setting = s;
  compileProcess = new QProcess;
  runProcess = new QProcess;

  if(!s->isInEnvironmentPath())
    {
      QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
      env.insert("PATH", env.value("Path") + ";" + setting->path());
      compileProcess->setProcessEnvironment(env);
    }

  connect(compileProcess,SIGNAL(readyReadStandardError()),this,SLOT(standardError()));
  connect(compileProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(standardOutput()));

  connect(runProcess,SIGNAL(readyReadStandardError()),this,SLOT(runStandardError()));
  connect(runProcess,SIGNAL(readyReadStandardOutput()),this,SLOT(runStandardOutput()));
}

void BuildManager::setMakeFile(const QString &makefile)
{
  makeFile = makefile;
}

void BuildManager::setSourceFile(const QString &sourceFile)
{
  _sourceFile = sourceFile;
}

void BuildManager::setWorkingDir(const QString &workingDir)
{
  this->workingDir = workingDir;
}

QString BuildManager::getWorkingDir() const
{
  return workingDir;
}

bool BuildManager::build()
{
  getError = false;

  if(_sourceFile.isNull())
    {
      compileProcess->start(setting->compiler()->make(), QStringList()<< setting->compiler()->makeCommand() <<makeFile);
    }
  else
    {
      if(Bases::fileSuffix(_sourceFile) == "c")
        compileProcess->start(setting->compiler()->CC(),QStringList()<<  _sourceFile);
      else
        compileProcess->start(setting->compiler()->CXX(), QStringList()<< _sourceFile);

      _sourceFile.clear();
    }

  if(compileProcess->waitForFinished())
    return !getError;

  return false;
}


bool BuildManager::hasError()
{
  return getError;
}

void BuildManager::standardError()
{
  QByteArray error = compileProcess->readAllStandardError();

  if(!error.isEmpty())
    {
      newStandardError(QString::fromUtf8(error).trimmed());
      getError = true;
    }
}

void BuildManager::standardOutput()
{
  QByteArray out = compileProcess->readAllStandardOutput();

  if(!out.isEmpty())
    newStandardOutput(QString::fromUtf8(out).trimmed());
}

void BuildManager::runStandardError()
{
  QByteArray error = runProcess->readAllStandardError();

  if(!error.isEmpty())
    {
      newRunStandardError(QString::fromUtf8(error).trimmed());
      getError = true;
    }
}

void BuildManager::runStandardOutput()
{
  QByteArray out = runProcess->readAllStandardOutput();

  if(!out.isEmpty())
    newRunStandardOutput(QString::fromUtf8(out).trimmed());
}

bool BuildManager::useShadowBuild() const
{
  return _useShadowBuild;
}

void BuildManager::setUseShadowBuild(bool useShadowBuild)
{
  _useShadowBuild = useShadowBuild;
}


void BuildManager::abort(const QString &exeName)
{

#ifdef Q_OS_WIN32
  compileProcess->start("TASKKILL",QStringList()<<"/F"<<"/IM"<<luncher);
#else
  procss->start("pidof",QStringList()<<luncher);

  procss->waitForFinished();
  //pid = procss->readAllStandardOutput()
  procss->start("kill",QStringList()<<"-9"<< procss->readAllStandardOutput());
#endif

}

bool BuildManager::programCompiled(const QString &destDirTarget) const
{
  return QFileInfo(destDirTarget).exists();
}


bool BuildManager::executeProgram(const QString &program,const QString &arguments,const QString& workingDir,
                              bool runInTerminal)
{
  if(!QFileInfo(program).exists())
    return false;

  runProcess->setWorkingDirectory(workingDir);

  if(runInTerminal)
    runProcess->start(luncher, QStringList()<<program<<arguments);
  else
    runProcess->start(program, QStringList()<<arguments);

  connect(runProcess,SIGNAL(finished(int)),this,SLOT(getProgramExitCode(int)));

  return true;
}

void BuildManager::getProgramExitCode(int exitCode)
{
  emit programFinished(tr("Program exit with code") + " " + QString::number(exitCode));
}

void BuildManager::clean()
{
  compileProcess->start(setting->compiler()->make(), QStringList()<< setting->compiler()->makeCommand() <<makeFile<<"clean");
}

CompilerSetting *BuildManager::Setting() const
{
  return setting;
}
