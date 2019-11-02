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

#include "config.h"
#include "core_constants.h"

Config::Config(const QString &name) : SettingsManager(name)
{

}

Config *Config::fromOther(const Config &other)
{
  Config * config = new Config(other.name());
  config->setSettings(other.toSettings());
  return config;
}

Config::~Config()
{

}

QString Config::destDirTarget() const
{
  return "$(DESTDIR)/$(TARGET)." + ext();
}

QString Config::ext() const
{
  switch(toInt(Core::Project::TEMPLATE))
    {
    case App:
#ifdef Q_OS_WIN32
      return "exe";
      #endif
#ifdef Q_OS_LINUX
      return "run";
      #endif
#ifdef Q_OS_MAC
      return "app";
#endif
    case Lib:
      return "a";
    case SharedLib:
#ifdef Q_OS_WIN32
      return "dll";
      #endif
#ifdef Q_OS_LINUX
      return "so";
      #endif
#ifdef Q_OS_MAC
      return "dylib";

#endif

    }

  return QString();

}

QString Config::type() const
{
  return Core::Project::CONFIG;
}


