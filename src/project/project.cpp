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

#include "project.h"

#include <bases.h>

#include "runconfig.h"
#include "core_constants.h"

using namespace Core::Project;

Project::Project(const QString &projectName) :
  SettingsDocument(projectName)
{

}

bool Project::addSubProject(const QString &subProjectName)
{  
  QDomElement item = rootFirstChild();

  while(!item.isNull())
    {
      if(item.tagName() == Core::Project::SUBPROJECTS)
        {
          add(Core::Project::PATH,item,Bases::relativeFilePath(path(),subProjectName),true);
          break;
        }

      item = item.nextSibling().toElement();
    }

  if(Bases::out(name(), document().toString()))
    {
      Project * subProject = new Project(subProjectName);

      subProjects.insert(subProjectName,subProject);

      return true;
    }
  else
    return false;

}

void Project::removeSubProject(const QString &subProject)
{
  QDomElement item = rootFirstChild();

  if(removeItem(item,Core::Project::SUBPROJECTS,Bases::relativeFilePath(
                  path(),subProject),true))
    {
      subProjects.remove(subProject);
      Bases::out(name(),document().toString());
    }
}

QString Project::type() const
{
  return Core::Project::PROJECT;
}

Project * Project::subProject(const QString& subProjectName)
{
  return subProjects.value(subProjectName);
}

QString Project::makeFile()  const
{
  QString customMakeFile = string(Core::Project::MAKEFILE);

  if(customMakeFile.isEmpty())
    return baseName() + "." +currentConfiguration()->name();
  else
    return customMakeFile;
}

void Project::deleteFile(const QString &fileName,const QString &tagName)
{
  QDomElement item = rootFirstChild();

  if(removeItem(item,tagName,fileName,true))
    {
      QStringList paths = stringList(tagName);
      paths.removeOne(fileName);

      addSetting(tagName,paths);

      Bases::out(name(),document().toString());
    }
}

void Project::addConfigPath(const QString &path,const QString &element)
{
  QDomElement item = settingsFirstChild(currentConfiguration());
  addSettingsManagerPath(currentConfiguration(),item,path,element);
}


Config *Project::currentConfiguration() const
{
  return _configs[this->toInt(CURRENT_CONFIG)];
}

Config *Project::config(int index) const
{
  return _configs[index];
}

bool Project::load()
{
  if(SettingsDocument::load()){
      foreach(QString subProjectName,stringList(SUBPROJECTS))
        {
          Project * subProject = new Project(subProjectName);

          subProjectName = QDir(path()).absoluteFilePath(subProjectName);
          subProjectName = QDir(subProjectName).absolutePath();

          subProjects.insert(subProjectName,subProject) ;
        }
      return true;
    }

  return false;
}

QMap<QString, Project *> Project::toSubProjects()
{
  return subProjects;
}

void Project::readSettings(SettingsManager *settingsManager,QDomElement &item)
{
  while(!item.isNull())
    {
      QString itemTagName = item.tagName();
      QDomElement child = item.firstChild().toElement();

      if(child.isNull())
        settingsManager->addSetting(item.tagName(),item.text());
      else if(itemTagName == Core::Project::CONFIG)
        {
          Config * config = new Config(item.attribute(Core::Project::NAME));

          SettingsDocument::readSettings(config,child);

          _configs << config;

        }
      else if(itemTagName == Core::Project::RUNCONFIG)
        {
          RunConfig *  runConfig = new RunConfig(item.attribute(Core::Project::NAME));

          SettingsDocument::readSettings(runConfig,child);

          runConfigs <<runConfig;
        }
      else
        {
          if(child.attributes().count() == 1)
            settingsManager->addSetting(item.tagName(),readList(child));
          else
            settingsManager->addSetting(item.tagName(),readMap(child));
        }

      item = item.nextSibling().toElement();
    }



}

void Project::renameFile(const QString &tagName,const QString &fileName,const QString &renamedFile)
{
  QDomElement item = rootFirstChild();

  renamePath(item,tagName,fileName,renamedFile);
}

void Project::replaceConfigSetting(const QString &settingName,const QString &value)
{
  currentConfiguration()->addSetting(settingName,value);

  QDomElement item = settingsFirstChild(currentConfiguration());
  renameItem(item,settingName,value);
}

void Project::replaceRunConfigSetting(const QString &settingName,const QString &value)
{
  QDomElement item = rootFirstChild();

  currentRunConfig()->addSetting(settingName,value);
  renameAttribute(item,Core::Project::RUNCONFIG,settingName,value);
}

bool Project::hasSubProjects() const
{
  return ! subProjects.isEmpty();
}

// return name() stringList(SOURCES) ,headerfiles,resourcefiles and otherfiles
// does not return searchdirs or something like that

QStringList Project::toFiles() const
{
  QStringList files ;

  foreach(QString filesSetting ,filesSettings())
    {
      files<<stringList(filesSetting);
    }

  return files;
}

QList<RunConfig *> Project::runConfigurations() const
{
  return runConfigs;
}

RunConfig *Project::currentRunConfig() const
{
  return runConfigs[this->toInt(CURRENT_RUNCONFIG)];
}

void Project::addRunConfig(RunConfig * runConfig)
{
  runConfigs << runConfig;
  saveSettings(runConfig);
}

void Project::cloneRunConfig(int index, const QString &newRunConfigName)
{
  RunConfig * clonedRConfig = runConfigs[index];
  clonedRConfig->setName(newRunConfigName);

  addRunConfig(clonedRConfig);
}

void Project::removeRunConfig(int index)
{
  QString rConfigName = runConfigs[index]->name();

  runConfigs.removeAt(index);

  QDomElement item = rootFirstChild();

  if(removeItem(item,Core::Project::RUNCONFIG,rConfigName))
    Bases::out(name(),document().toString());
}

void Project::renameRunConfig(int index, const QString &newRunConfigName)
{
  RunConfig * rConfig = runConfigs[index];

  QDomElement item = rootFirstChild();
  renameAttribute(item,Core::Project::RUNCONFIG,Core::Project::NAME,rConfig->name(),newRunConfigName);
  rConfig->setName(newRunConfigName);

}

QList<Config *> Project::configs() const
{
  return _configs;
}

QStringList Project::configsNames() const
{
  QStringList configs_names;

  foreach(Config * config,configs())
    configs_names<< config->name();

  return configs_names;
}

void Project::addConfig(Config * config)
{
  _configs<<config;
  saveSettings(config);
}

void Project::addConfigs(const QList<Config *> &configs)
{
  foreach (Config * config, configs) {
      addConfig(config);
    }
}

void Project::cloneConfig(int index,const QString &newConfigName)
{
  Config * clonedConfig = _configs[index];
  clonedConfig->setName(newConfigName);

  addConfig(clonedConfig);
}

void Project::removeConfig(int index)
{
  QString configName = _configs[index]->name();

  _configs.removeAt(index);

  QDomElement item = rootFirstChild();

  if(removeItem(item,Core::Project::CONFIG,configName))
    Bases::out(name(),document().toString());
}

void Project::renameConfig(int index , const QString &newConfigName)
{
  Config * config = _configs[index];

  QDomElement item = rootFirstChild();
  renameAttribute(item,Core::Project::CONFIG,Core::Project::NAME,config->name(),newConfigName);
  config->setName(newConfigName);
}

QStringList Project::filesSettings()
{
  return QStringList()<< Core::Project::SOURCES
                      <<Core::Project::HEADERS
                     <<Core::Project::RESOURCES
                    <<Core::Project::OTHERFILES;
}

bool Project::isSmcProject(const QString &fileName)
{
 return fileName.endsWith(".smc");
}








