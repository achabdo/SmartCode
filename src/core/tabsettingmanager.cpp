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

#include "tabsettingmanager.h"

#include <QTabWidget>
#include <QTreeWidget>

#include "settingsmanager.h"
#include "core_constants.h"

TabSettingManager::TabSettingManager()
{
  TabSetting *tabSetting;
  tabSetting =  new TabSetting;
  tabSetting->addContent(QObject::tr("Libs"),Core::Project::LIBS);

  tabsSettings.append(tabSetting);

  tabSetting = new TabSetting;
  tabSetting->addContent(QObject::tr("Executable Directories"),Core::Project::EXECUTABLES);
  tabSetting->addContent(QObject::tr("Compiler"),Core::Project::INCLUDES);
  tabSetting->addContent(QObject::tr("Linker"),Core::Project::INCLUDELIBS);
  tabSetting->addContent(QObject::tr("Resource compiler"),Core::Project::RESCOMPILER);

  tabsSettings.append(tabSetting);

  tabSetting =  new TabSetting;
  tabSetting->createAddButtonMenu();
  tabSetting->addContent(QObject::tr("Custom Variables"),Core::Project::CUSTOMVARIABLES,false);
  tabSetting->setCurrentListHeaderLabels(QStringList()<<"Key"<<"Value");


  tabsSettings.append(tabSetting);
}

void TabSettingManager::load(SettingsManager * settings)
{

  foreach (TabSetting *tabSetting, tabsSettings) {

      tabSetting->clearAll();

      for(int i = 0; i < tabSetting->tabWidget()->count() ;i++)
        {
          QString elem = tabSetting->tabElement(i);

          if(tabSetting->currentList()->columnCount() == 1)
            tabSetting->addItems(settings->stringList(elem),i);
          else
            {
              QMap<QString,QVariant> map = settings->map(elem);

              foreach(QString key,map.keys())
                {
                  tabSetting->addItem(QStringList()<<key<<map.value(key).toString());
                }
            }
        }
    }

}

void TabSettingManager::save(SettingsManager *settings)
{
  foreach (TabSetting *tabSetting, tabsSettings) {

      for(int i = 0; i < tabSetting->tabWidget()->count() ;i++)
        {
          QString elem = tabSetting->tabElement(i);

          if(tabSetting->currentList()->columnCount() == 1)
            settings->addSetting(elem,tabSetting->itemsText(i));
          else
            {

              QMap<QString,QVariant> map;

              for(int row = 0; row< tabSetting->listCount(i);row++)
                {
                  map.insert(tabSetting->itemText(row,0),tabSetting->itemText(row,1));

                }

              settings->addSetting(elem,map);

            }
        }
    }
}

TabSetting * TabSettingManager::tabSetting(int index) const
{
  return tabsSettings.at(index);
}

