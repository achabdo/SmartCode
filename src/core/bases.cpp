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

#include "bases.h"

#include <QFile>
#include <QTextStream>

Bases::Bases()
{

}

Bases::~Bases()
{

}

bool Bases::out(const QString &fileName,const QString &text)
{
  QFile file(fileName);

  if(!file.open(QFile::WriteOnly))
    return false;

  QTextStream out(&file);
  out << text;
  file.close();
  return true;
}


bool Bases::isSourceFile(const QString &fileName)
{
  return  fileName.contains(sourceFilesReg());
}

bool Bases::isHeaderFile(const QString &fileName)
{
    return  fileName.contains(headerFilesReg());
}

bool Bases::isResourceFile(const QString &fileName)
{
    return  fileName.contains(resourceFilesReg());
}

bool Bases::isOtherFile(const QString &fileName)
{
    return  fileName.contains(otherFilesReg());
}

QString Bases::headerSource(const QString &fileName)
{
  if(fileName.contains(sourceFilesReg()))
    {
      QRegExp rx("*.*");
      rx.setPatternSyntax(QRegExp::Wildcard);
    }
}

QRegExp Bases::sourceFilesReg()
{
  return QRegExp("[^\\.]\\.(cpp|cxx|c|cc)$");
}

QRegExp Bases::headerFilesReg()
{
  return QRegExp("[^\\.]\\.(h|hxx)$");
}

QRegExp Bases::resourceFilesReg()
{
  return QRegExp("[^\\.]\\.(rc|qrc|png|ico|jpeg|jpg)$");
}

QRegExp Bases::otherFilesReg()
{
  return QRegExp("*.*",Qt::CaseSensitive,QRegExp::Wildcard);
}



