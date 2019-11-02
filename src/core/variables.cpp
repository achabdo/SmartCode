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

#include "variables.h"

Variables::Variables()
{

}

void Variables::addVariable(const QString &varName, const QString &value)
{
  _values.insert(varName,value);
}

void Variables::unset(const QString &varName)
{
  _values.remove(varName);
}

QStringList Variables::variables()
{
  return _values.keys();
}

QString Variables::value(const QString &varName)
{
  return _values.value(varName);
}

void Variables::clear()
{
  _values.clear();
}

QString Variables::evaluateExpression(QString expr)
{
  QRegExp exprReg("\\$\\((\\w+)\\)");

  while(exprReg.indexIn(expr,0) != -1)
    {
      QString var = exprReg.cap(1);
      expr.replace(exprReg.cap(0),value(var));
    }

  return expr;
}

QString Variables::evaluateVariable(const QString &var)
{
  return evaluateExpression(value(var));
}


void Variables::fromList(const QStringList &list)
{
  foreach (const QString &str, list) {
      int pos = str.indexOf(QLatin1Char('='), 1);
      if (pos == -1) {
          addVariable(str,QString());
        } else {
          addVariable(str.left(pos), str.mid(pos+1));
        }
    }
}


QStringList Variables::toList()
{
  QStringList list;

  foreach (const QString &var, variables()) {
      if (value(var).isNull())
        list << QString(var);
      else
        list << QString(var + QLatin1Char('=') + value(var));
    }

  return list;
}




