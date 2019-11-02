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

#include "compiler.h"

Compiler::Compiler(const QString &path)
{
  this->path = path;
}

QString Compiler::CC() const
{
  return QString();
}

QString Compiler::CXX() const
{
  return QString();
}

QString Compiler::dynamicLibLinker() const
{
  return QString();
}

QString Compiler::staticLibLinker() const
{
  return QString();
}

QString Compiler::make() const
{
  return QString();
}

QString Compiler::makeCommand() const
{
  return QString();
}

QString Compiler::resourceCompiler() const
{
  return QString();
}

QString Compiler::debugger() const
{
  return QString();
}

void Compiler::setPath(const QString &path)
{
  this->path = path;
}

QString Compiler::getPath() const
{
  return path;
}

QList<CompilerOptionsCategory *> Compiler::flags() const
{
  return QList<CompilerOptionsCategory *>();
}


void Compiler::autoDetecte()
{

}

void Compiler::parse(const QString &)
{

}


