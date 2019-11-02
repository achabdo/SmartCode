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

#include <QProcess>
#include <QRegularExpression>

#include <bases.h>
#include <host.h>

#include "gcc.h"
#include "compileroptionscategory.h"
#include "compileroption.h"
#include "environment.h"

Gcc::Gcc(const QString &path) : Compiler(path)
{
  const char FILE_PATTERN[] = "(<command[ -]line>|([A-Za-z]:)?[^:]+):";
  const char COMMAND_PATTERN[] = "^(.*?[\\\\/])?([a-z0-9]+-[a-z0-9]+-[a-z0-9]+-)?(gcc|g\\+\\+)(-[0-9\\.]+)?(\\.exe)?: ";

  regExp.setPattern(QLatin1Char('^') + QLatin1String(FILE_PATTERN)
                    + QLatin1String("(\\d+):(\\d+:)?\\s+((fatal |#)?(warning|error|note):?\\s)?([^\\s].+)$"));

  regExpIncluded.setPattern(QString::fromLatin1("\\bfrom\\s") + QLatin1String(FILE_PATTERN)
                            + QLatin1String("(\\d+)(:\\d+)?[,:]?$"));

  regExpGccNames.setPattern(QLatin1String(COMMAND_PATTERN));
}

QString Gcc::name() const
{
  return "GCC";
}

void Gcc::autoDetecte(const QString &compiler)
{
  Environment env = Environment::systemEnvironment();

  QString compilerPath = env.searchInPath(compiler);

  if(!compilerPath.isEmpty())
    {
      env.appendOrSetPath(Bases::path(compilerPath));

      QProcess process;
      process.setEnvironment(env.toList());

      process.start("g++",QStringList()<<"-dumpversion");
      process.waitForFinished();

      //QString version = p.readAllStandardOutput().trimmed();
    }
}

//QString Gcc::make() const
//{
//  Environment env = Environment::systemEnvironment();

//  QString make = QLatin1String("make");
//  QString tmp = env.searchInPath(make);
//  return tmp.isEmpty() ? make : tmp;
//}

QString Gcc::CC() const
{
  return "gcc";
}

QString Gcc::CXX() const
{
  return "g++";
}

QString Gcc::dynamicLibLinker() const
{
  return "g++";
}

QString Gcc::staticLibLinker() const
{
  return "ar";
}

QString Gcc::make() const
{
  return "make";
}

QString Gcc::makeCommand() const
{
  return  "-f";
}

QString Gcc::resourceCompiler() const
{
  return QString();
}

QString Gcc::debugger() const
{
  return QString();
}

QList<CompilerOptionsCategory *> Gcc::flags()
{
  CompilerOptionsCategory *category;
  CompilerOption * option;

  category = new CompilerOptionsCategory(tr("C Options"));

  option = new CompilerOption(tr("support all ANSI standard C programs"));
  option->addBoolFlags("-ansi");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("Do not recognize asm, inline or typeof as a keyword"));
  option->addBoolFlags("-fno-asm");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("support some aspects of traditional C compilers"));
  option->addBoolFlags("-traditional");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("support some aspects of traditional C preprocessors"));
  option->addBoolFlags("-traditional-cpp");
  category->addCompilerOption(option);


  category = new CompilerOptionsCategory(tr("Preprocessor"));

  option = new CompilerOption("Do not search system directories");
  option->addBoolFlags("-nostdinc");
  category->addCompilerOption(option);

  option = new CompilerOption("Preprocess only");
  option->addBoolFlags("-E");
  category->addCompilerOption(option);

  category = new CompilerOptionsCategory(tr("Debugging"));

  option = new CompilerOption(tr("Debug Level"));
  //option->setText("Debug level");
  option->addEmptyFlag();
  option->addFlag("Minimum","-g1");
  option->addFlag("Regular","-g");
  option->addFlag("Maximum","-g3");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("Generate prof information"));
  option->addBoolFlags("-p");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("Generate gprof information"));
  option->addBoolFlags("-pg");
  category->addCompilerOption(option);

  category = new CompilerOptionsCategory(tr("Warnings"));

  option = new CompilerOption("Check syntax only");
  option->addBoolFlags("-fsyntax-only");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("Warning messages level"));
  option->addEmptyFlag();
  option->addFlag(tr("Inhibit"),"-w");
  option->addFlag(tr("All"),"-Wall");
  option->addFlag(tr("Extra"),"-Wextra");
  category->addCompilerOption(option);

  option = new CompilerOption("Issue all the warnings\errors demanded by strict ISO C");
  option->addEmptyFlag();
  option->addFlag("warnings","-pedantic");
  option->addFlag("errors","-pedantic-errors");
  category->addCompilerOption(option);

  option = new CompilerOption(tr("Stop compiling after first error"));
  option->addBoolFlags("-Wfatal-errors");
  category->addCompilerOption(option);

  option = new CompilerOption("Make all warnings into errors");
  option->addBoolFlags("-Werror");
  category->addCompilerOption(option);

  option = new CompilerOption("Implicit conversion warnings");
  option->addBoolFlags("-Wconversion");
  category->addCompilerOption(option);

  category = new CompilerOptionsCategory(tr("Optimization"));
  option = new CompilerOption("optimization level");
  //option->setText("optimization level");

  option->addEmptyFlag();
  option->addFlag("Basic","-O");
  option->addFlag("Medium","-O2");
  option->addFlag("High","-O3");
  option->addFlag("Size","-Os");

  category->addCompilerOption(option);
}

void Gcc::parse(const QString &line)
{
  QString lne = line.trimmed();

  if (lne.startsWith(QLatin1String("ERROR:")) ||
      lne == QLatin1String("* cpp failed")) {

      newMessage(Message::Error,lne);
      return;
    }

  QRegularExpressionMatch match;

  match = regExpGccNames.match(lne);
  if (match.hasMatch()) {
      QString description = lne.mid(match.capturedLength());
      Message::MessageType type = Message::Error;
      if (description.startsWith(QLatin1String("warning: "))) {
          type = Message::Warning;
          description = description.mid(9);
        } else if (description.startsWith(QLatin1String("fatal: ")))  {
          description = description.mid(7);
        }
      newMessage(type, description);
      return;
    }

  match = regExp.match(lne);

  if (match.hasMatch()) {
      int lineno = match.captured(3).toInt();
      Message::MessageType type = Message::Unknown;
      QString description = match.captured(8);
      if (match.captured(7) == QLatin1String("warning"))
        type = Message::Warning;
      else if (match.captured(7) == QLatin1String("error") ||
               description.startsWith(QLatin1String("undefined reference to")) ||
               description.startsWith(QLatin1String("multiple definition of")))
        type = Message::Error;

      if (match.captured(5).startsWith(QLatin1Char('#')))
        description = match.captured(5) + description;

      newMessage(type, description, match.captured(1), lineno);
      return;

    }

  match = regExpIncluded.match(lne);
  if (match.hasMatch()) {
      newMessage(Message::Unknown,
                 lne.trimmed() /* description */,
                 match.captured(1) /* filename */,
                 match.captured(3).toInt() /* linenumber */
                 );
      return;

    } else if (lne.startsWith(QLatin1Char(' '))) {
      expandDescription(lne);
      return;
    }

  newMessage(Message::Unknown,lne);
}


Mingw::Mingw(const QString &path) : Gcc(path)
{

}

QString Mingw::name() const
{
  return "Mingw";
}

QString Mingw::make() const
{
  return "mingw32-make";
}

void Gcc::doFlush()
{
  emit addMessage(_currentMessage);
}

void Gcc::newMessage(const Message::MessageType &_type, const QString &description
                     , const QString &fileName, int lineno)
{
  doFlush();
  _currentMessage = Message(_type,description,fileName,lineno);
}

void Gcc::expandDescription(const QString &desc )
{
  _currentMessage.info.append(QLatin1Char('\n'));
  _currentMessage.info.append(desc);
}
