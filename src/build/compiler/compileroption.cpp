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

#include "compileroption.h"

CompilerOption::CompilerOption(const QString &text, int defaultFlag, QObject *parent)
  :QObject(parent),_defaultFlag(defaultFlag)
{
  _text = text;
  _currentFlag = _defaultFlag;
}

void CompilerOption::setText(const QString &text)
{
  _text =  text;
}

void CompilerOption::addFlag(const QString &description, const QString &arg)
{
  _flags << new Flag(description,arg);
}

void CompilerOption::addBoolFlags(const QString &yesArg,const QString &noArg)
{
  Flag *f ;
  f = new Flag(tr("No"),noArg);
  _flags << f;
  f = new Flag(tr("Yes"),yesArg);
  _flags <<  f;
}

void CompilerOption::addEmptyFlag()
{
  addFlag(tr("None"),QString());
}

QString CompilerOption::text() const
{
  return _text;
}

QList<Flag*> CompilerOption::flags() const
{
  return _flags;
}

int CompilerOption::defaultFlag() const
{
  return _defaultFlag;
}
int CompilerOption::currentFlag() const
{
  return _currentFlag;
}

void CompilerOption::setCurrentFlag(int currentFlag)
{
  _currentFlag = currentFlag;
}



