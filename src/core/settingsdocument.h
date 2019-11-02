#ifndef SETTINGSDOCUMENT_H
#define SETTINGSDOCUMENT_H

#include <core_global.h>
#include "settingsmanager.h"
#include <QtXml>


class CORESHARED_EXPORT SettingsDocument : public SettingsManager
{

public:
  enum SettingType{Settings,Custom};
  explicit SettingsDocument(const QString &name);

  void clear(QDomElement &item);
  void clear(QDomElement &parent, const QString &tagName);

  virtual bool load();

  QString path() const;
  QString baseName() const;
  QString baseNamePath() const;

  void addPath(const QString &path, const QString &element);
  void addPaths(const QStringList &paths, const QString &element);

  void updateSettings(SettingsManager *oldSettings,SettingsManager *newSettings);

  void write();
protected:

  QDomElement add(const QString &setting,
                  QDomElement &parent , const QString &value = QString(), bool createTextNode = false);

  void addList(const QString &settingName, const QStringList &list, QDomElement &parent);

  void addMap(const QString &settingName,
              const QMap<QString, QVariant> &map, QDomElement &parent);

  bool removeItem(QDomElement &item, const QString &tagName, const QString &value, bool rmChild = false);

  void renamePath(QDomElement &item,const QString &tagName,
                  const QString &oldValue,const QString &newValue);
  void renameItem(QDomElement &item,const QString &value);
  void renameItem(QDomElement &item,
                  const QString &tagName, const QString &value);
  void saveSettings(SettingsManager *settingsManager);

  void renameAttribute(QDomElement &item, const QString &tagName, const QString &attr
                       , const QString &oldValue, const QString &newValue = QString());

  QDomDocument document() const;
  QDomElement settingsFirstChild(SettingsManager *settings);
  QDomElement rootFirstChild();
  QDomElement toRoot();

  QStringList readList(QDomElement &path);

  void addSettingsManagerPath(SettingsManager *settingsManager, QDomElement &item, const QString &path, const QString &element);
  virtual void readSettings(SettingsManager *settingsManager, QDomElement &item);
  void clearSettings(SettingsManager *settings,const QString &tagName);

  QMap<QString, QVariant> readMap(QDomElement &item);
  QDomElement toGroup(const QString &groupeName);
private:
  void writeSettings(SettingsManager * settingsManager, QDomElement &item);
  bool openDocument();

  QDomDocument doc;
  QString _name;

  bool addPathItem(QDomElement &item, const QString &tagName, const QString &pathName);

};

#endif // SETTINGSDOCUMENT_H
