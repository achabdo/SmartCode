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

#include "buildvariables.h"
#include <QFileInfo>

BuildVariables::BuildVariables()
{

}

bool BuildVariables::evaluateCondition(const QString &exp)
{
  QRegExp rx("^(equal|greatherThen|lessThen|contains)\\(([^\\,].+),([^\\)].+)\\)$");
  rx.indexIn(exp);

  enum { OPERATOR, VARIABLE, VALUE} ;

  return resolveCondition(rx.cap(OPERATOR),rx.cap(VARIABLE),rx.cap(VALUE));
}

bool BuildVariables::resolveCondition(const QString &exp, const QString &var, const QString &value)
{
  if(exp ==  QLatin1String("equals"))
    return evaluateExpression(var) == evaluateExpression(value);
  else if(exp ==  QLatin1String("greatherThen"))
    return evaluateExpression(var) > evaluateExpression(value);
  else if(exp ==  QLatin1String("lessThen"))
    return evaluateExpression(var) < evaluateExpression(value);
  else if(exp == QLatin1String("contains"))
    {
      QStringList list = evaluateExpression(var).split(QLatin1Char(';'));
      return list.contains(evaluateExpression(value));
    }

  return false;
}

QStringList BuildVariables::projectVariables() const
{
  return QStringList()<<"DESTDIR_TARGET"<<"OBJECTS_DIR";
}

