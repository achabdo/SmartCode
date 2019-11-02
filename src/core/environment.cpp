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

#include "environment.h"

#include <QDir>
#include <QProcess>

#include "host.h"

Environment::Environment()
{

}


QString Environment::searchInPath(const QString &fileName)
{
  QStringList paths = value(QLatin1String("PATH")).split(pathListSeparator());

  foreach(QString path,paths)
    {
      QString pathFileName = path + QLatin1Char('/') + fileName;

      QFileInfo info(pathFileName);

      if(info.exists() && info.isFile() && info.isExecutable())
        return pathFileName;
    }

  return QString();
}

QChar Environment::pathListSeparator()
{
  if(Host::isWindowsHost())
    return QLatin1Char(';');
  else if(Host::isLinuxHost())
    return QLatin1Char(':');

  return QChar();
}

Environment Environment::systemEnvironment()
{
  Environment env ;
  env.fromList(QProcess::systemEnvironment());
  return env;
}

void Environment::appendOrSet(const QString &key, const QString &value, const QString &sep)
{
    const QString &_key = (Host::isWindowsHost() ? key.toUpper() : key);
    QMap<QString, QString>::iterator it = _values.find(_key);
    if (it == _values.end()) {
       _values.insert(_key, value);
    } else {
        // Append unless it is already there
        const QString toAppend = sep + value;
        if (!it.value().endsWith(toAppend))
            it.value().append(toAppend);
    }
}

void Environment::prependOrSet(const QString&key, const QString &value, const QString &sep)
{
    const QString &_key = (Host::isWindowsHost() ? key.toUpper() : key);
    QMap<QString, QString>::iterator it = _values.find(_key);
    if (it == _values.end()) {
        _values.insert(_key, value);
    } else {
        // Prepend unless it is already there
        const QString toPrepend = value + sep;
        if (!it.value().startsWith(toPrepend))
            it.value().prepend(toPrepend);
    }
}

void Environment::appendOrSetPath(const QString &value)
{
    appendOrSet(QLatin1String("PATH"), QDir::toNativeSeparators(value),
            QString(pathListSeparator()));
}

void Environment::prependOrSetPath(const QString &value)
{
    prependOrSet(QLatin1String("PATH"), QDir::toNativeSeparators(value),
            QString(pathListSeparator()));
}
