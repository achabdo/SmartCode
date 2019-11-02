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

#include "configmanager.h"

#include <compiler/compilersetting.h>

#include "config.h"
#include "core_constants.h"

ConfigManager::ConfigManager(CompilerSetting *_compilerSetting, QObject *parent) : QObject(parent)
{
  compilerSetting = _compilerSetting;
}

ConfigManager::~ConfigManager()
{

}

Config * ConfigManager::addDefaultConfig(const QString &configName)
{
  Config * config = new Config(configName);

  config->addSetting(Core::Project::DESTDIR,"$(PROJECTDIR)\\$(CONFIG)");
  config->addSetting(Core::Project::OBJECTSDIR,"$(CONFIG)");
  config->addSetting(Core::Project::TARGET,"$(PROJECTNAME)");

  return config;

}

Config *ConfigManager::addDebugConfig(const QString &name)
{
  Config * debug = addDefaultConfig(name);
  debug->addSetting(Core::Compiler::CXXFLAGS,compilerSetting->stringList(Core::Compiler::CXXFLAGS_DEBUG));

  return debug;
}

Config *ConfigManager::addReleaseConfig(const QString &name)
{
  Config * release = addDefaultConfig(name);
  release->addSetting(Core::Compiler::CXXFLAGS,compilerSetting->stringList(Core::Compiler::CXXFLAGS_RELEASE));

  return release;
}

