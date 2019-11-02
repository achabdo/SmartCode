#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include "core_global.h"
#include <QVariant>

class CORESHARED_EXPORT  SettingsManager
{

public:
  SettingsManager(const QString &name = QString());
  SettingsManager(const SettingsManager * other);

  void addSetting(const QString &name, const QVariant &value);
  QVariant setting(const QString &name) const;

  void setName(const QString &name);
  QString name() const;

  virtual QString type()const;
  void clearSetting(const QString &name);

  inline QString string(const QString &settingName) const
  {return setting(settingName).toString();}

  inline QStringList stringList(const QString &settingName) const
  {return setting(settingName).toStringList();}

  inline QMap<QString,QVariant> map(const QString &settingName) const
  {return setting(settingName).toMap();}

  inline int toInt(const QString &settingName) const{
    return setting(settingName).toInt();}

  inline bool toBool(const QString &settingName) const{
    return setting(settingName).toBool();}

  QStringList allSettingsNames() const;

  QVariantMap toSettings() const;
  void setSettings(const QVariantMap &newSettings);
private:
  QString _name;
  QVariantMap settings;

};

#endif // SETTINGSMANAGER_H
