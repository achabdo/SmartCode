#ifndef TABSETTINGMANAGER_H
#define TABSETTINGMANAGER_H

#include "core_global.h"

#include <QList>

#include "tabsetting.h"

class SettingsManager;

class CORESHARED_EXPORT TabSettingManager
{
public:
  enum Content
  {
    Linker,
    SearchPaths,
    BuildVariables
  };

  TabSettingManager();

  void load(SettingsManager *settings);
  void save(SettingsManager *settings);

  TabSetting * tabSetting(int index) const;
private:
  QList<TabSetting*> tabsSettings;
};

#endif // TABSETTINGMANAGER_H
