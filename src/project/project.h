#ifndef PROJECT_H
#define PROJECT_H

#include "project_global.h"
#include "config.h"
#include <QObject>
#include <settingsdocument.h>

class RunConfig;

class PROJECTSHARED_EXPORT Project : public SettingsDocument
{
public:

  explicit Project(const QString &projectName);

  QString type() const;
  QString makeFile()  const;

  Config* currentConfiguration() const;
  Config* config(int index) const;

  bool addSubProject(const QString &subProjectName);

  void deleteFile(const QString &fileName, const QString &tagName);

  void renameFile(const QString &tagName,const QString &fileName,const QString &renamedFile);

  void replaceConfigSetting(const QString &settingName, const QString &value);

  bool hasSubProjects() const;

  void removeSubProject(const QString &subProject);

  Project * subProject(const QString& subProjectName);

  QStringList toFiles() const;

  QList<RunConfig*> runConfigurations() const;

  QList<Config *> configs() const;

  void addConfigPath(const QString &path, const QString &element);

  QStringList configsNames() const;

  void addConfig(Config *config);
  void addConfigs(const QList<Config*> & configs);
  void cloneConfig(int index, const QString &newConfigName);
  void removeConfig(int index);
  void renameConfig(int index, const QString &newConfigName);

  RunConfig *currentRunConfig() const;

  void addRunConfig(RunConfig * runConfig);
  void cloneRunConfig(int index, const QString &newRunConfigName);
  void removeRunConfig(int index);
  void renameRunConfig(int index, const QString &newRunConfigName);

  void replaceRunConfigSetting(const QString &settingName, const QString &value);
  static QStringList filesSettings() ;

  static bool isSmcProject(const QString &fileName);

  bool load();

  QMap<QString,Project*> toSubProjects();

protected:
  void readSettings(SettingsManager *settingsManager, QDomElement &item);
private:
  QMap<QString,Project*> subProjects;

  QList<Config*>  _configs;
  QList<RunConfig*>  runConfigs;
};

#endif // PROJECT_H
