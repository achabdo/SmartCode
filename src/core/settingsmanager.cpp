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

#include "settingsmanager.h"

SettingsManager::SettingsManager(const QString &name)
{
  _name = name;
}

SettingsManager::SettingsManager(const SettingsManager *other)
{
     foreach(QString settingName,other->allSettingsNames())
       {
         this->addSetting(settingName,other->setting(settingName));
       }
}

void SettingsManager::addSetting(const QString &name, const QVariant &value)
{
  settings.insert(name,value);
}

void SettingsManager::clearSetting(const QString &name)
{
  settings.remove(name);
}

QStringList SettingsManager::allSettingsNames() const
{
  return settings.keys();
}

QVariant SettingsManager::setting(const QString &name) const
{
  return settings.value(name);
}

QVariantMap SettingsManager::toSettings() const
{
  return settings;
}

void SettingsManager::setSettings(const QVariantMap &newSettings)
{
  settings = newSettings;
}

void SettingsManager::setName(const QString &name)
{
  _name = name;
}

QString SettingsManager::name() const
{
  return _name;
}

QString SettingsManager::type() const
{
  return QString();
}



