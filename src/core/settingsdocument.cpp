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

#include "settingsdocument.h"

#include <QLineEdit>
#include <QTreeWidget>
#include <QComboBox>
#include <tabsetting.h>

#include "bases.h"
#include "core_constants.h"

SettingsDocument::SettingsDocument(const QString &name) :SettingsManager(name)
{
  _name = name;
}


bool SettingsDocument::load()
{
  if(!openDocument())
    return false;

  QDomElement item = toRoot().firstChild().toElement();

  readSettings(this,item);

  return true;

}

QString SettingsDocument::path() const
{
  return Bases::path(_name);
}

QString SettingsDocument::baseName() const
{
  return Bases::baseName(_name);
}

QString SettingsDocument::baseNamePath() const
{
  return Bases::baseNamePath(_name);
}

void SettingsDocument::readSettings(SettingsManager *settingsManager,QDomElement &item)
{
  while(!item.isNull())
    {
      QDomElement child = item.firstChild().toElement();

      if(child.isNull())
        settingsManager->addSetting(item.tagName(),item.text());
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


bool SettingsDocument::openDocument()
{
  QFile file(_name);

  if(!file.open(QFile::ReadOnly))
    return false;

  doc.setContent(&file);
  file.close();

  return true;
}

QDomDocument SettingsDocument::document() const
{
  return doc;
}

QDomElement SettingsDocument::add(const QString &setting, QDomElement &parent,
                                  const QString &value,bool createTextNode)
{
  QDomElement elem;

  elem = doc.createElement(setting);

  if(!value.isNull())
    {
      if(createTextNode)
        elem.appendChild(doc.createTextNode(value));
      else
        elem.setAttribute(Core::Project::NAME,value);
    }

  parent.appendChild(elem);

  return elem;
}

void SettingsDocument::addList(const QString &settingName,const QStringList &list, QDomElement &parent){
  QDomElement itemList = add(settingName,parent);

  QDomElement elem;

  foreach(const QString &element,list)
    {
      elem = doc.createElement(Core::Project::VARIABLE);
      elem.setAttribute(Core::Project::NAME,element);

      itemList.appendChild(elem);
    }
}

void SettingsDocument::addMap(const QString &settingName,const QMap<QString,QVariant> &map
                              , QDomElement &parent)
{
  QDomElement itemMap = add(settingName,parent);

  QDomElement elem;

  foreach(QString key,map.keys())
    {
      elem = doc.createElement(Core::Project::VARIABLE);

      elem.setAttribute(Core::Project::NAME,key);
      elem.setAttribute(Core::Project::VALUE,map.value(key).toString());

      itemMap.appendChild(elem);
    }
}

bool SettingsDocument::removeItem(QDomElement &item,const QString &tagName,const QString &value,bool rmChild)
{
  while(!item.isNull())
    {
      if (item.tagName() == tagName)
        {
          if(rmChild)
            {
              QDomElement path = item.firstChild().toElement();

              while(!path.isNull())
                {
                  if(path.attribute(Core::Project::NAME) == value)
                    {
                      item.removeChild(path);

                      return true;
                    }

                  path = path.nextSibling().toElement();
                }
            }
          else
            {
              if(item.attribute(Core::Project::NAME) == value)
                {
                  QDomElement parent = item.parentNode().toElement();

                  parent.removeChild(item);

                  return true;
                }
            }
        }
      item = item.nextSibling().toElement();
    }

  return false;
}

void SettingsDocument::renameItem(QDomElement &item,const QString &value)
{
  item.replaceChild(doc.createTextNode(value),item.firstChild());
  Bases::out(name(),doc.toString());
}

void SettingsDocument::renameItem(QDomElement &item,
                                  const QString &tagName,const QString &value)
{

  while(!item.isNull())
    {
      if (item.tagName() == tagName)
        {
          renameItem(item,value);
          break;
        }

      item = item.nextSibling().toElement();
    }
}

bool SettingsDocument::addPathItem(QDomElement &item,const QString &tagName,const QString &pathName)
{
  while(!item.isNull())
    {
      if (item.tagName() == tagName)
        {
          QDomElement path = doc.createElement(Core::Project::PATH);
          path.setAttribute(Core::Project::NAME,pathName);

          item.appendChild(path);

          return true;
        }

      item = item.nextSibling().toElement();
    }

  return false;
}

void SettingsDocument::addSettingsManagerPath(SettingsManager * settingsManager,QDomElement &item,
                                              const QString &path,const QString &element)
{
  QStringList paths = settingsManager->stringList(element);

  if(!paths.contains(path))
    {
      if(addPathItem(item,element,path))
        {
          paths << path;
          settingsManager->addSetting(element,paths);
          Bases::out(name(),doc.toString());
        }
    }
}

void SettingsDocument::addPath(const QString &path,const QString &element)
{
  QDomElement item = rootFirstChild();
  addSettingsManagerPath(this,item,path,element);
}


void SettingsDocument::addPaths(const QStringList &paths,const QString &element)
{
  foreach (QString path, paths) {
      addPath(path,element);
    }
}


void SettingsDocument::renamePath(QDomElement &item,const QString &tagName,
                                  const QString &oldValue,const QString &newValue)
{
  while(!item.isNull())
    {
      if (item.tagName() == tagName)
        {
          QDomElement path = item.firstChild().toElement();

          while(!path.isNull())
            {
              if(path.attribute(Core::Project::NAME) == oldValue)
                {
                  path.setAttribute(Core::Project::NAME,newValue);
                  break;
                }

              path = path.nextSibling().toElement();
            }
        }
      item = item.nextSibling().toElement();
    }

  Bases::out(name(),doc.toString());
}

QStringList SettingsDocument::readList(QDomElement &path)
{
  QStringList list;

  while(!path.isNull())
    {
      list<<path.attribute(Core::Project::NAME);
      path = path.nextSibling().toElement();
    }

  return list;
}

QMap<QString,QVariant> SettingsDocument::readMap(QDomElement &item)
{
  QMap<QString,QVariant> map;

  while(!item.isNull())
    {
      map.insert(item.attribute(Core::Project::NAME),item.attribute(Core::Project::VALUE));
      item = item.nextSibling().toElement();
    }

  return map;
}

void SettingsDocument::write()
{
  doc.createComment("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>");

  QDomElement root;
  root = doc.createElement(type());
  doc.appendChild(root);

  writeSettings(this,root);
}

void SettingsDocument::saveSettings(SettingsManager * settingsManager)
{
  QDomElement root = toRoot();
  QDomElement item = add(settingsManager->type(),root,settingsManager->name());

  writeSettings(settingsManager,item);
}

QDomElement SettingsDocument::settingsFirstChild(SettingsManager *settings)
{
  QDomElement item = rootFirstChild();

  while(!item.isNull())
    {
      if(item.tagName() == settings->type() && item.attribute(Core::Project::NAME)
         == settings->name())
        {
          return item.firstChild().toElement();
        }

      item = item.nextSibling().toElement();
    }

  return QDomElement();
}

void SettingsDocument::clearSettings(SettingsManager *settings,const QString &tagName)
{
  QDomElement item = settingsFirstChild(settings);
  clear(item,tagName);
}

void SettingsDocument::updateSettings(SettingsManager *oldSettings, SettingsManager *newSettings)
{
  QDomElement item = settingsFirstChild(newSettings);

  while(!item.isNull())
    {
      QString settingName = item.tagName();

      QVariant oldSetting = oldSettings->setting(settingName);
      QVariant newSetting = newSettings->setting(settingName);

      if(oldSetting != newSetting)
        {
          int settingType = oldSetting.type() ;

          switch(settingType)
            {
            case QVariant::String:
            case QVariant::Int:
              renameItem(item,newSetting.toString());
              break;
            case QVariant::StringList:
              clear(item);
              addList(settingName,newSetting.toStringList(),item);
              break;
            case QVariant::Map:
              clear(item);
              addMap(settingName,newSetting.toMap(),item);
              break;
            }
        }

      item = item.nextSibling().toElement();
    }

  Bases::out(_name,doc.toString());

}

void SettingsDocument::writeSettings(SettingsManager *settingsManager, QDomElement &item)
{
  foreach (QString settingName,settingsManager->allSettingsNames())
    {
      int settingType = settingsManager->setting(settingName).type() ;

      if(settingType == QVariant::String)
        add(settingName,item,settingsManager->string(settingName),true);

      else if(settingType == QVariant::Int){
          add(settingName,item,QString::number(settingsManager->toInt(settingName)),true);
        }
      else if(settingType == QVariant::StringList)
        {
          addList(settingName,settingsManager->stringList(settingName),item);
        }
      else if(settingType == QVariant::Map){
          addMap(settingName,settingsManager->map(settingName),item);
        }
    }

  Bases::out(_name,doc.toString());
}

void SettingsDocument::renameAttribute(QDomElement &item,const QString &tagName,
                                       const QString &attr,const QString &oldValue,const QString &newValue)
{
  while(!item.isNull())
    {
      if (item.tagName() == tagName)
        {
          if(newValue.isNull())
            {
              item.setAttribute(attr,oldValue);
              break;
            }
          else
            {
              if(item.attribute(attr) == oldValue)
                {
                  item.setAttribute(attr,newValue);
                  break;
                }
            }
        }

      item = item.nextSibling().toElement();
    }

  Bases::out(name(),doc.toString());
}

QDomElement SettingsDocument::rootFirstChild()
{
  return toRoot().firstChild().toElement();
}

QDomElement SettingsDocument::toRoot()
{
  return doc.documentElement();
}

QDomElement SettingsDocument::toGroup(const QString &groupeName)
{
  QDomElement item = rootFirstChild();

  while(!item.isNull())
    {
      if(item.tagName() == Core::Project::GROUP)
        {
          if(item.attribute(Core::Project::NAME) == groupeName)
            return item;
        }

      item = item.nextSibling().toElement();
    }

  return QDomElement();
}

void  SettingsDocument::clear(QDomElement &item)
{
  QDomElement valueElement = item.firstChild().toElement();

  while(!valueElement.isNull())
    {
      item.removeChild(valueElement);

      valueElement = item.firstChild().toElement();
    }

  Bases::out(name(),doc.toString());

}

void SettingsDocument::clear(QDomElement &parent,const QString &tagName)
{
  while(!parent.isNull())
    {
      if (parent.tagName() == tagName)
        {
          clear(parent);
          break;
        }

      parent = parent.nextSibling().toElement();
    }
}

